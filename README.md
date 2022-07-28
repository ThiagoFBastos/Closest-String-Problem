# Closest String Problem

Seja $S$ uma sequência de cadeias {$S_1$, $S_2$, $S_3$, ... , $S_n$} com $|S_i|$ = $m$ que possuem caracteres de um alfabeto $\Sigma$. O problema da string mais próxima consiste em encontrar uma cadeia T também de comprimento m, em que a maior distância de Hamming entre $T$ e todas as cadeias da entrada $S$ é mínima, ou seja, $T$ = $argmin_T$ ${max_{1 \le i \le n}{d(S_i, T)}}$

## Instâncias
* Chimani (/instancias/csp_rnd_tar)
* McClure (/instancias/mcclure_tar)
* Hufsky (/instancias/hufsky_tar)

## Pré-Requisitos
* g++ com suporte ao c++17
* programa make

## Uso
1. Execute o comando make na pasta com arquivo makefile
2. execute ./[programa] [arquivo com as instâncias]

## Solução inicial 1
O algoritmo consiste em gerar uma string em que cada posição 1 $\le$ $j$ $\le$ $m$
contém um caractere escolhido aleatoriamente dentre os caracteres presentes na
coluna $j$ das cadeias de entrada.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/sol_1.png)

No algoritmo 1 para cada coluna 1 $\le$ $j$ $\le$ $m$, a sequência $\Sigma$, inicialmente vazia
(linha 2), é preenchida com os caracteres dessa coluna (linhas 3 à 5) e a partir dela
um elemento é escolhido aleatoriamente e atribuído a $T_j$ (linha 6).

## Solução inicial 2
O algoritmo 2 que foi baseado no trabalho feito por (SANTOS, 2018) em seu
mestrado segue uma estratégia gulosa para a construção da cadeia e para isso escolhe
para cada posição um dos caracteres mais frequentes nessa posição de forma aleatória.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/sol-2.png)

No algoritmo 2 para cada coluna 1 $\le$ j $\le$ $m$, um contador para os caracteres do alfabeto $\Sigma$, a variável $frq$, é inicializada com zeros (linha 2) e logo após a frequência de cada caractere é contabilizada (linhas 3 à 5) e com isso um dos caracteres que possuem a frequência máxima presentes em caracteres é escolhido aleatoriamente e atribuído a string $T$ na posição $j$ (linhas 8 à 13).

## Solução inicial 3
O algoritmo 3 consiste em gerar uma string $T$ ao associar cada uma de suas posições à uma das cadeias de entrada de tal forma que a diferença entre a quantidade recebida por uma string difira em no máximo uma unidade das demais. Com a
associação realizada, os caracteres nas posições atribuídas às cadeias da entrada são
atribuídos nas mesmas posições na string $T$.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/sol-3.png)

No algoritmo 3, a sequência S da entrada tem a ordem de suas strings embarahadas (linha 1), a permutação com elementos de 1 até $m$ também é embaralhada (linha) 2, e para cada 1 $\le$ $i$ $\le$ $n$, as posições que estão na permutação $P$ no intervalo
[$pos$, $pos$ + $fracao$ − 1] são usadas para indexar os elementos de $S_i$ e atribuí-los nas
mesmas posições em $T$ e caso i $\le$ ($m$ $mod$ $n$) o intervalo usado para indexação é
[$pos$, $pos$ + $fracao$] (linhas 7 à 15) e com isso pos é incrementado com o tamanho do intervalo.

## Solução inicial 4

O algoritmo 4 consiste em gerar uma string T mesclando as strings da entrada
em uma ordem pré-definida. Sendo que cada mescla destina $\frac{1}{i}$ das posições que
possuem caracteres diferentes para uma das strings e o resto para a outra.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/sol-4.png)

No algoritmo 4 a sequência $S$ tem a ordem de suas strings embaralhadas (linha 2)
e então a sequência de strings $T$ que pussui $S_1$ como primeiro elemento (linha 3) é construida: para cada 2 $\le$ $i$ $\le$ $n$ as posições $j$ em que $S_{i, j}$ $\ne$ $T_{i − 1, j}$ são inseridas em posicoes que é embaralhada aleatoriamente logo após isso e os primeiros $\lceil\frac{|posicoes|}{i}\rceil$ seus elementos são usados para indexar os caracteres de $S_i$ e atribuí-los nas mesmas posições em $T_i$.

## Simulated Annealing (/sa/sa-[versão])

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/SA.png)

No algoritmo 5, uma string é gerada pelo algoritmo de solução inicial (linha 1), a
maior distância de hamming entre a candidata à solução e uma das strings da entrada é
encontrada (linha 3), uma posição (posicao) entre [1, $m$] é selecionada aleatoriamente
(linha 8), uma posição ($id$\text{_}$cadeia$) entre [1, $n$] é selecionada aleatoriamente, a string
vizinho é gerada ao se substituir candidatoposicao por $S_{id_cadeia}$,posicao (linha 11), um
número real entre [0, 1] é gerado (linha 14).

### Parâmetros
* $\epsilon$ = $10^{-3}$
* $\rho$ = $0.99$
* $T_0$ = 500


	
## Simulated Annealing Paralelo (/sa/sa-[versão]-sap-[versão])
![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/sap.png)

### Pré-Requisitos
* POSIX
	
## ILS (/ils/ils-[versão])
![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/ils.png)

### Parâmetros
* MAX_ITERACOES = 100
* MAX_VEZES = 10

### Busca local
![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/ils-sa.png)

#### Parâmetros
* $\rho$ = 0.99
* $\epsilon$ = $10^{-2}$
* $\beta$ = $0.3$

### Temperatura Inicial
![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/T0.png)

#### Parâmetros
* $\alpha$ = 1.1
* $\epsilon$ = $10^{-2}$
* $\zeta$ = 0.95

### Pré-Requisitos
* SSE
* SSE2
* SSE3
* SSE4.1
* SSSE4.2
* POSIX

## GA (/ga)
![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/g.png)
	
