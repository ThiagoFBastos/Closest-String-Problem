#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <x86intrin.h>
#include <climits>

#define DEBUG

#define _and _mm_and_si128
#define _sub _mm_sub_epi32
#define _add _mm_add_epi32
#define _load _mm_load_si128
#define _set _mm_set1_epi32
#define _eq _mm_cmpeq_epi32
#define _max _mm_max_epi32
#define _store _mm_store_si128
#define _xor _mm_xor_si128

using namespace std;

#ifdef DEBUG
long long A = chrono::steady_clock::now().time_since_epoch().count();
#endif

const double zero = 1e-2, red = 0.99;
const int MAX_ITER = 100;
const int MAX_VEZES = MAX_ITER / 10;

default_random_engine gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> p(0, 1);
uniform_int_distribution<int> rnd_pos, rnd_word;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n, m, k, l, a, *w;
char *word;
vector<char> alpha;

void load(const char* filename) {
	fstream fs(filename, ios_base :: in);
	
	if(!fs.is_open()) {
		cout << "nao foi aberto\n";
		exit(0);
	}
	
	fs >> a >> n >> m;

	alpha.resize(a);
	k = m + (16 - m % 16) % 16;
	l = n + (4 - n % 4) % 4;

	word = new char[l * m];
	posix_memalign((void**)&w, 16, l * m * sizeof(int));

	memset(word, 0, sizeof(char) * m * l);
	memset(w, 0, sizeof(int) * m * l);

	for(int i = 0; i < a; ++i) fs >> alpha[i];
	
	for(int i = 0; i < n; ++i) {
		string s;
		fs >> s;
		for(int j = 0; j < m; ++j) w[j * l + i] = word[j * l + i] = s[j];
	}
	
	fs.close();
}

void solucao_inicial(char *s) {
	vector<int> p(m);
	iota(p.begin(), p.end(), 0);
	int fatia = m / n, resto = m % n;
	shuffle(p.begin(), p.end(), rng);
	for(int i = 0, k = 0; i < n; ++i) {
		int q = fatia + (resto > 0);
		for(int j = 0; j < q; ++j, ++k) s[k] = word[k * l + rnd_word(gen)];
		resto = max(0, resto - 1);
	}
}

void copy(char* dest, char *src, int n) {
	for(int i = 0; i < n; i += 16) _store((__m128i*)&dest[i], _load((__m128i*)&src[i]));
}

char *tmp0, *tmp1;
int *dist;

int SA(char* s) {
	double T = 10;
	int bestfit, fitness = 0, val[4] __attribute__((aligned (16)));
	
	copy(tmp1, s, m);

	__m128i ZERO = _set(0), ONE = _set(1);
	for(int i = 0; i < n; i += 4) _store((__m128i*)&dist[i], ZERO);

	for(int j = 0; j < m; ++j) {
		__m128i S = _set(s[j]);
		for(int i = 0; i < n; i += 4)
			_store((__m128i*)&dist[i], _add(_load((__m128i*)&dist[i]), _and(_xor(_eq(_load((__m128i*)&w[l * j + i]), S), ONE), ONE)));
	}

	for(int i = n; i < l; ++i) dist[i] = 0;
	for(int i = 0; i < n; ++i) if(dist[i] > fitness) fitness = dist[i];	

	bestfit = fitness;

	while(true) {
		int aceito = 0;
		for(int i = 0; i < m; ++i) {
			int pos = rnd_pos(gen), delta;
			char from = tmp1[pos], to = word[pos * l + rnd_word(gen)];
			__m128i MAX = _set(0), FROM = _set(from), TO = _set(to);
			for(int i = 0; i < n; i += 4) {
				__m128i D = _load((__m128i*)&w[pos * l + i]);
				MAX = _max(MAX, _add(_load((__m128i*)&dist[i]), _sub(_and(_eq(FROM, D), ONE), _and(_eq(TO, D), ONE))));
			}
			_store((__m128i*)&val, MAX);
			delta = max(max(val[0], val[1]), max(val[2], val[3])) - fitness;
			if(delta <= 0 || p(gen) < exp(-delta / T)) ++aceito;
		}
		if(aceito >= 0.95 * m) break;
		T *= 1.1;
	}

	while(T > zero) {
		for(int i = 0; i < m; ++i) {
			int pos = rnd_pos(gen), delta;
			char from = tmp1[pos], to = word[pos * l + rnd_word(gen)];
	
			__m128i MAX = _set(0), FROM = _set(from), TO = _set(to);

			for(int i = 0; i < n; i += 4) {
				__m128i D = _load((__m128i*)&w[pos * l + i]);
				MAX = _max(MAX, _add(_load((__m128i*)&dist[i]), _sub(_and(_eq(FROM, D), ONE), _and(_eq(TO, D), ONE))));
			}

			_store((__m128i*)&val, MAX);
			delta = max(max(val[0], val[1]), max(val[2], val[3])) - fitness;

			if(delta <= 0 || p(gen) < exp(-delta / T)) {
				tmp1[pos] = to;
				fitness += delta;

				if(fitness < bestfit) {
					bestfit = fitness;
					copy(s, tmp1, m);
				}

				for(int i = 0; i < n; i += 4) {
					__m128i D = _load((__m128i*)&w[pos * l + i]);
					_store((__m128i*)&dist[i], _add(_load((__m128i*)&dist[i]), _sub(_and(_eq(FROM, D), ONE), _and(_eq(TO, D), ONE))));
				}
			}
		}

		T *= red;
	}

	return bestfit;
}

int main(int argc, char* argv[]) {
	char *solucao;
	ios_base :: sync_with_stdio(false);
	
	load(argv[1]);

	rnd_pos = uniform_int_distribution<int>(0, m - 1);
	rnd_word = uniform_int_distribution<int>(0, n - 1);
	
	posix_memalign((void**)&solucao, 16, k * sizeof(char));
	posix_memalign((void**)&tmp0, 16, k * sizeof(char));
	posix_memalign((void**)&tmp1, 16, k * sizeof(char));
	posix_memalign((void**)&dist, 16, l * sizeof(int));

	memset(solucao, 0, k * sizeof(char));
	memset(tmp0, 0, k * sizeof(char));
	memset(tmp1, 0, k * sizeof(char));

	solucao_inicial(solucao);

	int fitness = SA(solucao);
	int nivel = 1, vezes = 1;

	for(int k = 0; k < MAX_ITER; ) {

		copy(tmp0, solucao, m);

		for(int i = 0; i < nivel; ++i) {
			int pos = rnd_pos(gen);
			tmp0[pos] = word[pos * l + rnd_word(gen)];
		}

		int f = SA(tmp0);

		if(fitness > f) {
			k = 0;
			nivel = vezes = 1;
			fitness = f;
			swap(tmp0, solucao);
		} else {
			++k;
			if(vezes < MAX_VEZES) ++vezes;
			else {
				++nivel;
				vezes = 1;
			}
		}
	}
	
	cout << "fitness = " << fitness << '\n';
	#ifdef DEBUG
	using namespace chrono;
	long long B = chrono::steady_clock::now().time_since_epoch().count();
	cout.precision(7);
	cout.setf(ios_base :: fixed);
	cout << "seconds = " << 1.0L * system_clock::period::num / system_clock::period::den * (B - A) << '\n';
	#endif

	return 0;
}
