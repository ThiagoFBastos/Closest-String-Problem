#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <array>

#define DEBUG

using namespace std;

#ifdef DEBUG
long long A = chrono::steady_clock::now().time_since_epoch().count();
#endif

const double zero = 1e-3, red = 0.99, TMAX = 500;

default_random_engine gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> p(0, 1);
uniform_int_distribution<int> rnd_pos, rnd_word;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

string merge(string& a, string& b, double r) {
	vector<int> p;
	string c(m, '.');
	for(int i = 0; i < m; ++i) {
		if(a[i] != b[i]) p.emplace_back(i);
		else c[i] = a[i];
	}
	shuffle(p.begin(), p.end(), rng);
	int n = ceil(r * int(size(p)));
	for(int i = 0; i < n; ++i) c[p[i]] = b[p[i]];
	for(int i = n; i < int(size(p)); ++i) c[p[i]] = a[p[i]];
	return c;
}


string solucao_inicial() {
	vector<int> P(n);
	iota(P.begin(), P.end(), 0);
	shuffle(P.begin(), P.end(), rng);
	string s = merge(word[P[0]], word[P[1]], 0.5);
	for(int i = 2; i < n; ++i) s = merge(s, word[P[i]], 1.0 / (i + 1));
	return s;
}

int main(int argc, char* argv[]) {
	ios_base :: sync_with_stdio(false);
	
	load(argv[1]);
	
	rnd_pos = uniform_int_distribution<int>(0, m - 1);
	rnd_word = uniform_int_distribution<int>(0, n - 1);
	
	vector<int> dist(n);
	vector<string> word_t(m);
	int fitness = 0, bestfit;
	double T = TMAX;
	string candidato, solucao;
	
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
	
	while(T > zero) {

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

		T *= red;
	}
	
	cout << "fitness = " << bestfit << '\n';
	#ifdef DEBUG
	using namespace chrono;
	long long B = chrono::steady_clock::now().time_since_epoch().count();
	cout.precision(7);
	cout.setf(ios_base :: fixed);
	cout << "seconds = " << 1.0L * system_clock::period::num / system_clock::period::den * (B - A) << '\n';
	#endif

	return 0;
}
