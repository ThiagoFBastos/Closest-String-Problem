#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <climits>

#define DEBUG

using namespace std;

#ifdef DEBUG
long long A = chrono::steady_clock::now().time_since_epoch().count();
#endif

struct solution {
	char *str;
	int *dist;
	int max_dist;
};

bool operator<(solution s, solution t) {
	return s.max_dist < t.max_dist;
}

const double ce = 0.3, cm = 0.5;

int n, m, a;
char *word, *word_t;
vector<char> alpha;

default_random_engine gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> p(0, 1);
uniform_int_distribution<int> rnd_word, rnd_pos;
uniform_int_distribution<char> rnd_char;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void load(const char* filename) {
	fstream fs(filename, ios_base :: in);

	if(!fs.is_open()) {
		cout << "nao foi aberto\n";
		exit(0);
	}
	
	fs >> a >> n >> m;

	word = new char[n * m];
	word_t = new char[n * m];
	alpha.resize(a);
	
	for(int i = 0; i < a; ++i) fs >> alpha[i];
		
	
	for(int i = 0; i < n; ++i) {
		string str;
		fs >> str;
		for(int j = 0; j < m; ++j) word_t[j * n + i] = word[i * m + j] = str[j];
	}
	
	fs.close();
}

void random_solution(solution& s) {
	s.max_dist = 0;
	memset(s.dist, 0, n * sizeof(int));
	for(int i = 0; i < m; ++i) {
		s.str[i] = word[rnd_word(gen) * m + i];
		for(int k = 0; k < n; ++k) {
			s.dist[k] += word_t[i * n + k] != s.str[i];
			s.max_dist = max(s.max_dist, s.dist[k]);
		}
	}
}

void crossover(solution& s, solution& t, solution& dest) {
	int pos = rnd_pos(gen) + 1;
	vector<int> p(m);
	iota(p.begin(), p.end(), 0);
	shuffle(p.begin(), p.end(), rng);
	for(int _i = 0; _i < pos; ++_i) {
		int i = p[_i];
		char from = dest.str[i], to = s.str[i];
		dest.str[i] = s.str[i];
		dest.max_dist = 0;
		for(int k = 0; k < n; ++k) dest.max_dist = max(dest.max_dist, dest.dist[k] + (word_t[i * n + k] == from) - (word_t[i * n + k] == to));
	}
	for(int _i = pos; _i < m; ++_i) {
		int i = p[_i];
		char from = dest.str[i], to = t.str[i];
		dest.str[i] = t.str[i];
		dest.max_dist = 0;
		for(int k = 0; k < n; ++k) dest.max_dist = max(dest.max_dist, dest.dist[k] + (word_t[i * n + k] == from) - (word_t[i * n + k] == to));
	}
}

void mutate(solution& s, double pb) {
	for(int j = 0; j < m; ++j) {
		if(p(gen) > pb) continue;
		char from = s.str[j], to = rnd_char(gen);
		s.max_dist = 0;
		for(int i = 0; i < n; ++i) s.max_dist = max(s.max_dist, s.dist[i] + (word_t[j * n + i] == from) - (word_t[j * n + i] == to));
	}
}

int main(int argc, char* argv[]) {
	ios_base :: sync_with_stdio(false);
	int melhor_dist = INT_MAX;

	load(argv[1]);
	
	rnd_word = uniform_int_distribution<int>(0, n - 1);
	rnd_pos = uniform_int_distribution<int>(0, m - 1);
	rnd_char = uniform_int_distribution<char>('a', 'a' + a - 1);
	vector<solution> pop(n), media_pop(n);

	for(int i = 0; i < n; ++i) {
		pop[i].dist = new int[n];
		pop[i].str = new char[m];
		random_solution(pop[i]);
		melhor_dist = min(melhor_dist, pop[i].max_dist);
	}

	int elite = n * ce;
	int media = cm * (n - elite);
	int pobre = n - elite - media;
	double pb = sqrt(m) / m;

	for(int i = 0; i < media; ++i) {
		media_pop[i].dist = new int[n];
		media_pop[i].str = new char[m];
		random_solution(media_pop[i]);
	}

	vector<pair<int, int>> ind(n);

	for(int k = 0; k < m; ++k) {
		int dist = INT_MAX;

		sort(pop.begin(), pop.end());

		for(int i = 0; i < n; ++i) ind[i] = make_pair(int(p(gen) * (m - pop[i].max_dist)), i);

		sort(ind.rbegin(), ind.rend());

		for(int i = 0; i < media; ++i) {
			int k = ind[2 * i % n].second, j = ind[(2 * i + 1) % n].second;
			crossover(pop[k], pop[j], media_pop[i]);
			mutate(media_pop[i], pb);
			dist = min(dist, media_pop[i].max_dist);
		}
		
		for(int i = 0; i < elite; ++i) {
			mutate(pop[i], pb);
			dist = min(dist, pop[i].max_dist);		
		}

		for(int i = n - pobre; i < n; ++i) {
			random_solution(pop[i]);
			dist = min(dist, pop[i].max_dist);
		}

		if(dist < melhor_dist) k = -1, melhor_dist = dist;
	}

	cout << "fitness = " << melhor_dist << '\n';
	#ifdef DEBUG
	using namespace chrono;
	long long B = chrono::steady_clock::now().time_since_epoch().count();
	cout.precision(7);
	cout.setf(ios_base :: fixed);
	cout << "seconds = " << 1.0L * system_clock::period::num / system_clock::period::den * (B - A) << '\n';
	#endif

	return 0;
}
