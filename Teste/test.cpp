#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#define CASAS 7
#define NUM_TESTES 3

int main(int argc, char* argv[]) {

	std :: ios_base :: sync_with_stdio(false);
	std :: cin.tie(nullptr);

	if(argc < 3) {
		std :: cout << "use ./test <caminho-do-executavel> <pasta-em-instancias> < <arquivo-com-as-instancias>\n";
		return 0;
	}

	int n;
	
	std :: vector<std :: string> paths;
	
	for(std :: string s; std :: getline(std :: cin, s); ) paths.push_back(s);
	
	for(auto& w : paths) {
		for(int i = 0; i < NUM_TESTES; ++i) {
			std :: string s = std :: string(argv[1]) + " " + "instancias/" + std :: string(argv[2]) + "/" + w + " >> output.txt";			
			system(s.c_str());
		}
	}
	
	std :: fstream fs("output.txt", std :: ios_base :: in);
	
	fs.precision(CASAS);
	fs.setf(std :: ios_base :: fixed);

	std :: cout.precision(CASAS);
	std :: cout.setf(std :: ios_base :: fixed);
	
	for(auto&s : paths) {
		long double seconds = 0, fitness = 0;
		for(int i = 0; i < NUM_TESTES; ++i) {
			std :: string fit, sc;
			int a0;
			long double a1;
			std :: getline(fs, fit);
			std :: getline(fs, sc);
			sscanf(fit.c_str(), "fitness = %d", &a0);
			sscanf(sc.c_str(), "seconds = %Lf", &a1);
			fitness += a0;
			seconds += a1;
		}
		std :: cout << "instância = " << s << '\n';
		std :: cout << "fitness = " << fitness / NUM_TESTES << '\n';
		std :: cout << "seconds = " << seconds / NUM_TESTES << '\n';
	}
	
	fs.close();
	system("echo -n "" > output.txt");

	return 0;
}
