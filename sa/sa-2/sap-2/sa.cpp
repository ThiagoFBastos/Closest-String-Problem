#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <pthread.h>
#include <array>

#define DEBUG

using namespace std;

#ifdef DEBUG
long long A = chrono::steady_clock::now().time_since_epoch().count();
#endif

const int NUM_THREADS = 8;

const double ZERO = 1e-3, RED = 0.99, TMAX = 500;

default_random_engine gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> p(0, 1);
uniform_int_distribution<int> rnd_pos, rnd_word;

int n, m, a;
vector<string> word;
vector<char> alpha;

void load(const char* filename) {
	fstream fs(filename, ios_base :: in);
	
	if(!fs.is_open()) {
		cout << "nao foi aberto\n";
		exit(0);
	}
	
	fs >> a >> n >> m;

	word.resize(n);
	alpha.resize(a);
		
	for(int i = 0; i < a; ++i) fs >> alpha[i];
	for(int i = 0; i < n; ++i) fs >> word[i];
	
	fs.close();	
}

string solucao_inicial() {
	string s(m, '.');	
	for(int j = 0; j < m; ++j) {
		array<int, 128> f;
		vector<char> ch;
		int maxn = 0;
		f.fill(0);
		for(int i = 0; i < n; ++i) maxn = max(maxn, ++f[word[i][j]]);
		for(int i = 0; i < 128; ++i) if(f[i] == maxn) ch.push_back(char(i));
		uniform_int_distribution<int> p(0, ch.size() - 1);
		s[j] = ch[p(gen)];
	}
	return s;
}

pthread_mutex_t mutex[NUM_THREADS];
pthread_t thread_id[NUM_THREADS];
string t_s[NUM_THREADS];
int t_f[NUM_THREADS], args[NUM_THREADS];
vector<int> t_d[NUM_THREADS];

void* SA(void* params) {
	
	vector<int> dist(n);
	vector<string> word_t(m);
	int fitness = 0, bestfit, next, id = *(int*)params;
	double T = TMAX;
	string candidato, solucao;
	
	next = (1 + id) % NUM_THREADS;
	candidato = solucao = solucao_inicial();

	for(int j = 0; j < m; ++j) {
		word_t[j].resize(n);
		for(int i = 0; i < n; ++i)
			word_t[j][i] = word[i][j];
	}

	for(int i = 0; i < n; ++i) {
		dist[i] = 0;
		for(int j = 0; j < m; ++j) dist[i] += word[i][j] != candidato[j];
		fitness = max(fitness, dist[i]);
	}
	
	bestfit = fitness;
	
	while(T > ZERO) {

		for(int i = 0; i < m; ++i) {
			int fit = 0, pos = rnd_pos(gen), delta;
			char from = candidato[pos], to = word_t[pos][rnd_word(gen)];
			
			for(int i = 0; i < n; ++i) 
				fit = max(fit, dist[i] + (word_t[pos][i] == from) - (word_t[pos][i] == to));
			
			delta = fit - fitness;
				
			if(delta <= 0 || p(gen) < exp(-delta / T)) {
				candidato[pos] = to;
				fitness = fit;

				if(fit < bestfit) {
					bestfit = fit;
					copy(candidato.begin(), candidato.end(), solucao.begin());
				}

				for(int i = 0; i < n; ++i)
					dist[i] += (word_t[pos][i] == from) - (word_t[pos][i] == to);
			}
		}

		pthread_mutex_lock(&mutex[next]);

		if(t_f[next] > fitness) {
			t_f[next] = fitness;
			copy(candidato.begin(), candidato.end(), t_s[next].begin());
			copy(dist.begin(), dist.end(), t_d[next].begin());
		}

		pthread_mutex_unlock(&mutex[next]);

		pthread_mutex_lock(&mutex[id]);

		if(t_f[id] != INT_MAX) {
			int delta = t_f[id] - fitness;
			if(delta <= 0 || p(gen) < exp(-delta / T)) {
				fitness = t_f[id];
				copy(t_s[id].begin(), t_s[id].end(), candidato.begin());
				copy(t_d[id].begin(), t_d[id].end(), dist.begin());
				if(t_f[id] < bestfit) {
					bestfit = t_f[id];
					copy(t_s[id].begin(), t_s[id].end(), solucao.begin());
				}
			}
			t_f[id] = INT_MAX;
		}

		pthread_mutex_unlock(&mutex[id]);		

		T *= RED;
	}

	*(int*)params = bestfit;

	return nullptr;
}

int main(int argc, char* argv[]) {
	int fitness = INT_MAX;

	ios_base :: sync_with_stdio(false);
	load(argv[1]);
	
	rnd_pos = uniform_int_distribution<int>(0, m - 1);
	rnd_word = uniform_int_distribution<int>(0, n - 1);
	
	for(int i = 0; i < NUM_THREADS; ++i) {
		t_s[i].resize(m);
		t_d[i].resize(n);
		t_f[i] = INT_MAX;
		args[i] = i;
		pthread_mutex_init(&mutex[i], nullptr);
	}

	for(int i = 0; i < NUM_THREADS; ++i) pthread_create(&thread_id[i], nullptr, SA, &args[i]); 
	
	for(int i = 0; i < NUM_THREADS; ++i) {
		pthread_join(thread_id[i], nullptr);
		fitness = min(fitness, args[i]);
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
