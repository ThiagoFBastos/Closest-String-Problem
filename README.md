<h1> Closest String Problem </h1>

<p>
	Seja S uma sequência de cadeias {S(1), S(2), S(3), . . . , S(n)} com |S(i)| = m que possuem
	caracteres de um alfabeto Σ. O problema da string mais próxima consiste em		
	encontrar uma cadeia T também de comprimento m, em que a maior distância
	de Hamming entre T e todas as cadeias da entrada S é mínima, ou seja, T =
	argmin(T) {max1≤i≤n{d(S(i), T)}}
</p>

<p>
	São apresentados três algoritmos heurísticos implementados em C++: Genetic Algorithm que possui apenas uma versão, ILS que possui quatro versões
e Simulated Annealing que possui 8 versões sendo 4 delas seriais e 4 paralelas.

</p>

<h3> Simulated Annealing </h3>
	Pasta: Está na pasta sa e cada versão k na pasta sa/sa-k
	
<h3> Simulated Annealing Paralelo </h3>
	Pasta: Está na pasta sa e cada versão k na pasta sa/sa-k/sap-k
	Pré-Requisitos: POSIX
	
<h3> ILS </h3>
	Pasta: Está na pasta ils e cada versão k na pasta ils/ils-k
	Pré-Requisitos: SSE, SSE2, SSE3, SSE4.1, SSSE4.2 e POSIX

<h3> GA </h3>
	Pasta: Está na pasta ga

<h3 > Instancias </h3>
	Chimani: Está na pasta instancias/csp_rnd_tar <br>
	McClure: Está na pasta instancias/mcclure_tar <br>
	Hufsky: Está na pasta instancias/hufsky_tar <br>
	
