
<style>
.two {
	margin-left: 25pt;
}
.three {
	margin-left: 50pt;
}
.four {
	margin-left: 75pt;
}
.five {
	margin-left: 90pt;
}
.six {
	margin-left: 105pt;
}
.seven {
	margin-left: 120pt;
}
</style>

<h1> Closest String Problem </h1>

<p class = "two">
	Seja S uma sequência de cadeias {S(1), S(2), S(3), . . . , S(n)} com |S(i)| = m que possuem
	caracteres de um alfabeto Σ. O problema da string mais próxima consiste em		
	encontrar uma cadeia T também de comprimento m, em que a maior distância
	de Hamming entre T e todas as cadeias da entrada S é mínima, ou seja, T =
	argmin(T) {max1≤i≤n{d(S(i), T)}}
</p>

<p class = "two">
	São apresentados três algoritmos heurísticos implementados em C++: Genetic Algorithm que possui apenas uma versão, ILS que possui quatro versões
e Simulated Annealing que possui 8 versões sendo 4 delas seriais e 4 paralelas.

</p>

<h3 class = "two"> Simulated Annealing </h3>

	<h4 class = "four"> Pasta </h4>
		<p class = "five"> Está na pasta sa e cada versão k na pasta sa/sa-k </p>

	<h4 class = "four"> Pré-requisitos </h4>
		<ul class = "five">
			<li> Nenhum</li>
		</ul>

	<h4 class="four"> Paralelo </h4>
		<p class = "five"> Cada versão paralela k está na pasta sa/sa-k/sap </p>

		<h4 class = "five"> Pré-requisitos </h4>
			<ul class = "six">
				<li> POSIX </li>
			</ul>

<h3 class = "two"> ILS </h3>
	<h4 class = "three"> Pasta </h4>
		<p class = "four"> Está na pasta ils e cada versão k na pasta ils/ils-k </p>

	<h4 class = "three"> Pré-requisitos </h4>
		<ul class = "four">
			<li> SSE, SSE2, SSE3, SSE4.1, SSSE4.2</li>
			<li> POSIX </li>
		</ul>

<h3 class = "two"> GA </h3>

	<h4 class = "three"> Pasta </h4>
		<p class = "four"> Está na pasta ga</p>

	<h4 class = "three"> Pré-requisitos </h4>
		<ul class = "four">
			<li> Nenhum </li>
		</ul>

<h3 class = "two"> Instancias </h3>
	<h4 class = "three"> Chimani </h4>
		<p class = "four">Está na pasta instancias/csp_rnd_tar</p>

	<h4 class = "three"> McClure </h4>
		<p class = "four">Está na pasta instancias/mcclure_tar</p>

	<h4 class = "three"> Hufsky </h4>
		<p class = "four">Está na pasta instancias/hufsky_tar</p>
	
