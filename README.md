# Closest String Problem

Seja $S$ uma sequência de cadeias { $S_1$, $S_2$, $S_3$, ... , $S_n$ } com $|S_i|$ = $m$ que possuem caracteres de um alfabeto $\Sigma$. O problema da string mais próxima consiste em encontrar uma cadeia T também de comprimento m, em que a maior distância de Hamming entre $T$ e todas as cadeias da entrada $S$ é mínima, ou seja, $T$ = $argmin_T$ ${max_{1 \le i \le n}{d(S_i, T)}}$

Este é o trabalho de conclusão de curso da minha graduação em Ciência da Computação e o [TCC](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/T_tulo_do_Trabalho.pdf) contém mais informações detalhadas sobre a pesquisa e os resultados.

## Instâncias

[informações sobre as instâncias](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/instancias/research_csp_cssp%20%5BTheoretical%20Computer%20Science%20_%20Theoretische%20Informatik%5D.pdf)

### Mcclure

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-mcclure.png)

Instâncias Mcclure com o limite inferior (lb) e o limite superior (ub) da resposta.

### Hufsky

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-hufsky.png)

Instâncias Hufsky com o limite inferior (lb) e o limite superior (ub) da resposta.

### Chimani

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-chimani.png)

Instâncias Chimani com o limite inferior da (lb) e o limite superior (ub) da resposta.

## Pré-Requisitos
* g++ com suporte ao c++17
* programa make

## Uso
1. Execute o comando make na pasta com arquivo makefile com: make
2. Execute: ./[programa] [arquivo com as instâncias]
3. Exemplo: ./sa ../../instancias/mcclure_tar/McClure-582-20-10-141.csp

## Solução inicial 1
O algoritmo consiste em gerar uma string em que cada posição 1 $\le$ $j$ $\le$ $m$
contém um caractere escolhido aleatoriamente dentre os caracteres presentes na
coluna $j$ das cadeias de entrada.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/sol_1.png)

No algoritmo 1 para cada coluna 1 $\le$ $j$ $\le$ $m$, a sequência $\Sigma$, inicialmente vazia
(linha 2), é preenchida com os caracteres dessa coluna (linhas 3 à 5) e a partir dela
um elemento é escolhido aleatoriamente e atribuído a $T_j$ (linha 6).

## Solução inicial 2
O algoritmo 2 que foi baseado no trabalho feito por (SANTOS, 2018) em seu
mestrado segue uma estratégia gulosa para a construção da cadeia e para isso escolhe
para cada posição um dos caracteres mais frequentes nessa posição de forma aleatória.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/sol-2.png)

No algoritmo 2 para cada coluna 1 $\le$ j $\le$ $m$, um contador para os caracteres do alfabeto $\Sigma$, a variável $frq$, é inicializada com zeros (linha 2) e logo após a frequência de cada caractere é contabilizada (linhas 3 à 5) e com isso um dos caracteres que possuem a frequência máxima presentes em caracteres é escolhido aleatoriamente e atribuído a string $T$ na posição $j$ (linhas 8 à 13).

## Solução inicial 3
O algoritmo 3 consiste em gerar uma string $T$ ao associar cada uma de suas posições à uma das cadeias de entrada de tal forma que a diferença entre a quantidade recebida por uma string difira em no máximo uma unidade das demais. Com a
associação realizada, os caracteres nas posições atribuídas às cadeias da entrada são
atribuídos nas mesmas posições na string $T$.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/sol-3.png)

No algoritmo 3, a sequência S da entrada tem a ordem de suas strings embarahadas (linha 1), a permutação com elementos de 1 até $m$ também é embaralhada (linha) 2, e para cada 1 $\le$ $i$ $\le$ $n$, as posições que estão na permutação $P$ no intervalo
[$pos$, $pos$ + $fracao$ − 1] são usadas para indexar os elementos de $S_i$ e atribuí-los nas
mesmas posições em $T$ e caso i $\le$ ($m$ $mod$ $n$) o intervalo usado para indexação é
[$pos$, $pos$ + $fracao$] (linhas 7 à 15) e com isso pos é incrementado com o tamanho do intervalo.

## Solução inicial 4

O algoritmo 4 consiste em gerar uma string T mesclando as strings da entrada
em uma ordem pré-definida. Sendo que cada mescla destina $\frac{1}{i}$ das posições que
possuem caracteres diferentes para uma das strings e o resto para a outra.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/sol-4.png)

No algoritmo 4 a sequência $S$ tem a ordem de suas strings embaralhadas (linha 2)
e então a sequência de strings $T$ que pussui $S_1$ como primeiro elemento (linha 3) é construida: para cada 2 $\le$ $i$ $\le$ $n$ as posições $j$ em que $S_{i, j}$ $\ne$ $T_{i − 1, j}$ são inseridas em posicoes que é embaralhada aleatoriamente logo após isso e os primeiros $\lceil\frac{|posicoes|}{i}\rceil$ seus elementos são usados para indexar os caracteres de $S_i$ e atribuí-los nas mesmas posições em $T_i$.

## Simulated Annealing (/sa/sa-[versão])

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/SA.png)

No algoritmo 5, uma string é gerada pelo algoritmo de solução inicial (linha 1), a
maior distância de hamming entre a candidata à solução e uma das strings da entrada é
encontrada (linha 3), uma posição (posicao) entre [1, $m$] é selecionada aleatoriamente
(linha 8), uma posição ($id_{-}cadeia$) entre [1, $n$] é selecionada aleatoriamente, a string
vizinho é gerada ao se substituir candidatoposicao por $S_{id_{-}cadeia,posicao}$ (linha 11), um
número real entre [0, 1] é gerado (linha 14).

### Solução inicial
Algoritmos de solução inicial 1, 2, 3 e 4

### Parâmetros
* $\epsilon$ = $10^{-3}$
* $\rho$ = $0.99$
* $T_0$ = 500

### Experimentos

Os testes foram realizados em um computador rodando o Ubuntu 18.04.3 LTS,
com um processador Intel Core i7-3770 com CPU 3.40GHz e memória de 8Gb, a
linguagem de programação utilizada foi a C++ versão 17, o compilador foi o g++
7.4.0 e as flags de compilação usadas foram: -O3, -funroll-loops, -march=native,
-mtune=native, -lpthread.

Cada instância foi executada três vezes para se obter a média aritmética dos
resultados e dos tempos.

#### Instâncias Mcclure

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-sa-mcclure.png)

A tabela 4.4 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $sa_1$ que contém o valor encontrado pelo SA usando
o algoritmo de solução inicial 1, a coluna $sa_2$ que contém o valor encontrado pelo SA
usando o algoritmo de solução inicial 2, a coluna $sa_3$ que contém o valor encontrado
pelo SA usando o algoritmo de solução inicial 3, a coluna $sa_4$ que contém o valor
encontrado pelo SA usando o algoritmo de solução inicial 4, a coluna $lb$ com o lower
bound da solução ótima, a coluna $ub$ com o upper bound da solução ótima, a coluna
$ER$ com o erro relativo entre o lower bound e a melhor resposta entre as versões do
SA e a coluna σ com o desvio padrão entre as respostas das versões do SA.


![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-sa-time-mcclure.png)

A tabela 4.5 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $sa_1$ que contém o tempo em segundos da execução
do SA usando o algoritmo de solução inicial 1 sobre a instância, a coluna $sa_2$ que
contém o tempo em segundos da execução do SA usando o algoritmo de solução
inicial 2 sobre a instância, a coluna $sa_3$ que contém o tempo em segundos da execução
do SA usando o algoritmo de solução inicial 3 sobre a instância e a coluna $sa_4$ que

#### Instâncias Hufsky

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-sa-hufsky.png)

A tabela 4.6 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $sa_1$ que contém o valor encontrado pelo SA usando
o algoritmo de solução inicial 1, a coluna $sa_2$ que contém o valor encontrado pelo SA
usando o algoritmo de solução inicial 2, a coluna $sa_3$ que contém o valor encontrado
pelo SA usando o algoritmo de solução inicial 3, a coluna $sa_4$ que contém o valor
encontrado pelo SA usando o algoritmo de solução inicial 4, a coluna $lb$ com o lower
bound da solução ótima, a coluna $ub$ com o upper bound da solução ótima, a coluna
$ER$ com o erro relativo entre o lower bound e a melhor resposta entre as versões do
SA e a coluna σ com o desvio padrão entre as respostas das versões do SA. Além
disso, o símbolo * indica quais das instâncias em que se foi possível alcançar a solução
ótima.

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-sa-time-hufsky.png)

A tabela 4.7 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $sa_1$ que contém o tempo em segundos da execução
do SA usando o algoritmo de solução inicial 1 sobre a instância, a coluna $sa_2$ que
contém o tempo em segundos da execução do SA usando o algoritmo de solução
inicial 2 sobre a instância, a coluna $sa_3$ que contém o tempo em segundos da execução
do SA usando o algoritmo de solução inicial 3 sobre a instância e a coluna $sa_4$ que
contém o tempo em segundos da execução do SA usando o algoritmo de solução
inicial 4 sobre a instância.

#### Instâncias Chimani

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-sa-chimani.png)

A tabela 4.8 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $sa_1$ que contém o valor encontrado pelo SA usando
o algoritmo de solução inicial 1, a coluna $sa_2$ que contém o valor encontrado pelo SA
usando o algoritmo de solução inicial 2, a coluna $sa_3$ que contém o valor encontrado
pelo SA usando o algoritmo de solução inicial 3, a coluna $sa_4$ que contém o valor
encontrado pelo SA usando o algoritmo de solução inicial 4, a coluna $lb$ com o lower
bound da solução ótima, a coluna $ub$ com o upper bound da solução ótima, a coluna
$ER$ com o erro relativo entre o lower bound e a melhor resposta entre as versões do
SA e a coluna σ com o desvio padrão entre as respostas das versões do SA. Além
disso, o símbolo * indica quais das instâncias em que se foi possível alcançar a solução
ótima.


![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-sa-time-chimani.png)

A tabela 4.9 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $sa_1$ que contém o tempo em segundos da execução
do SA usando o algoritmo de solução inicial 1 sobre a instância, a coluna $sa_2$ que
contém o tempo em segundos da execução do SA usando o algoritmo de solução
inicial 2 sobre a instância, a coluna $sa_3$ que contém o tempo em segundos da execução
do SA usando o algoritmo de solução inicial 3 sobre a instância e a coluna $sa_4$ que
contém o tempo em segundos da execução do SA usando o algoritmo de solução
inicial 4 sobre a instância.

## Simulated Annealing Paralelo (/sa/sa-[versão]-sap-[versão])
![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/sap.png)

Executa $NUM_{-}THREADS$ versões do algoritmo 5 cada uma delas identificada por um id inteiro único entre 1 e
$NUM_{-}THREADS$ e funciona de maneira similar ao serial, contudo em um determinado momento cada thread envia a solução corrente para a de identificador ($id$ $mod$ $NUM_{-}THREADS$) + 1.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/threads.png)

### Experimentos

Os testes foram realizados em um computador rodando o Ubuntu 18.04.3 LTS,
com um processador Intel Core i7-3770 com CPU 3.40GHz e memória de 8Gb, a
linguagem de programação utilizada foi a C++ versão 17, o compilador foi o g++
7.4.0 e as flags de compilação usadas foram: -O3, -funroll-loops, -march=native,
-mtune=native, -lpthread e $NUM_{-}THREADS$ = 8.

Cada instância foi executada três vezes para se obter a média aritmética dos
resultados e dos tempos.

#### Instâncias Mcclure

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-sap-mcclure.png)

A tabela 4.10 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $sap_1$ que contém o valor encontrado pelo SAP
usando o algoritmo de solução inicial 1, a coluna $sap_2$ que contém o valor encontrado
pelo SAP usando o algoritmo de solução inicial 2, a coluna sap3 que contém o valor
encontrado pelo SAP usando o algoritmo de solução inicial 3, a coluna $sap_4$ que
contém o valor encontrado pelo SAP usando o algoritmo de solução inicial 4, a coluna
$lb$ com o lower bound da solução ótima, a coluna $ub$ com o upper bound da solução
ótima, a coluna $ER$ com o erro relativo entre o lower bound e a melhor resposta
entre as versões do SAP e a coluna σ com o desvio padrão entre as respostas das
versões do SAP.

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-sap-time-mcclure.png)

A tabela 4.11 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $sap_1$ que contém o tempo em segundos da execução
do SAP usando o algoritmo de solução inicial 1 sobre a instância, a coluna $sap_2$ que
contém o tempo em segundos da execução do SAP usando o algoritmo de solução
inicial 2 sobre a instância, a coluna $sap_3$ que contém o tempo em segundos da
execução do SAP usando o algoritmo de solução inicial 3 sobre a instância e a coluna
$sap_4$ que contém o tempo em segundos da execução do SAP usando o algoritmo de
solução inicial 4 sobre a instância.

#### Instâncias Hufsky

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-sap-hufsky.png)

A tabela 4.12 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $sap_1$ que contém o valor encontrado pelo SAP
usando o algoritmo de solução inicial 1, a coluna $sap_2$ que contém o valor encontrado
pelo SAP usando o algoritmo de solução inicial 2, a coluna $sap_3$ que contém o valor
encontrado pelo SAP usando o algoritmo de solução inicial 3, a coluna $sap_4$ que
contém o valor encontrado pelo SAP usando o algoritmo de solução inicial 4, a coluna
$lb$ com o lower bound da solução ótima, a coluna $ub$ com o upper bound da solução
ótima, a coluna $ER$ com o erro relativo entre o lower bound e a melhor resposta
entre as versões do SAP e a coluna σ com o desvio padrão entre as respostas das
versões do SAP. Além disso, o símbolo * indica quais das instâncias em que se foi
possível alcançar a solução ótima.

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-sap-time-hufsky.png)

A tabela 4.13 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $sap_1$ que contém o tempo em segundos da execução
do SAP usando o algoritmo de solução inicial 1 sobre a instância, a coluna $sap_2$ que
contém o tempo em segundos da execução do SAP usando o algoritmo de solução
inicial 2 sobre a instância, a coluna $sap_3$ que contém o tempo em segundos da
execução do SAP usando o algoritmo de solução inicial 3 sobre a instância e a coluna
$sap_4$ que contém o tempo em segundos da execução do SAP usando o algoritmo de
solução inicial 4 sobre a instância.

#### Instâncias Chimani 

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-sap-chimani.png)

A tabela 4.14 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $sap_1$ que contém o valor encontrado pelo SAP
usando o algoritmo de solução inicial 1, a coluna $sap_2$ que contém o valor encontrado
pelo SAP usando o algoritmo de solução inicial 2, a coluna $sap_3$ que contém o valor
encontrado pelo SAP usando o algoritmo de solução inicial 3, a coluna $sap_4$ que
contém o valor encontrado pelo SAP usando o algoritmo de solução inicial 4, a coluna
$lb$ com o lower bound da solução ótima, a coluna $ub$ com o upper bound da solução
ótima, a coluna $ER$ com o erro relativo entre o lower bound e a melhor resposta
entre as versões do SAP e a coluna σ com o desvio padrão entre as respostas das
versões do SAP. Além disso, o símbolo * indica quais das instâncias em que se foi
possível alcançar a solução ótima.

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-sap-time-chimani.png)

A tabela 4.15 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $sap_1$ que contém o tempo em segundos da execução
do SAP usando o algoritmo de solução inicial 1 sobre a instância, a coluna $sap_2$ que
contém o tempo em segundos da execução do SAP usando o algoritmo de solução
inicial 2 sobre a instância, a coluna $sap_3$ que contém o tempo em segundos da
execução do SAP usando o algoritmo de solução inicial 3 sobre a instância e a coluna
$sap_4$ que contém o tempo em segundos da execução do SAP usando o algoritmo de solução inicial 4 sobre a instância.

### Pré-Requisitos
* POSIX
	
## ILS (/ils/ils-[versão])

Cada uma das soluções iniciais préviamente propostas 1, 2, 3 e 4 são utilizados
para gerar primeira solução ocasionando em 4 versões do ILS e o Simulated Annealing
5 é usado a fim de realizar a busca local.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/ils.png)

### Solução inicial
Algoritmos de solução inicial 1, 2, 3 e 4

### Parâmetros
* MAX_ITERACOES = 100
* MAX_VEZES = 10

### Busca local
O Simulated Annealing em 5 foi ligeiramente modificado para ser a busca local do ILS. A diferença
entre os dois algoritmos é que nesta versão a temperatura se torna dinâmica a fim
de minimizar a complexidade.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/ils-sa.png)

#### Parâmetros
* $\rho$ = 0.99
* $\epsilon$ = $10^{-2}$
* $\beta$ = $0.3$

### Temperatura Inicial
Caso a temperatura seja constante, a escolha de uma que seja agradável para
várias instâncias pode ser difícil de encontrar, além disso em um cenário específico o
valor pode estar muito acima do ideal. Por isso, um método que forneça a temperatura
de acordo com cada instância é sempre uma boa opção e por isso optamos em usar o
algoritmo proposto por (SOUZA, 2006) o 9 para realizar essa tarefa.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/T0.png)

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

### Experimentos

Os testes foram realizados em um computador rodando o Ubuntu 18.04.3 LTS, com um processador Intel Core i7-3770 com CPU 3.40GHz e memória de 8Gb, a linguagem de programação utilizada foi a C++ versão 17, o compilador foi o g++ 7.4.0 e as flags de compilação usadas foram: -O3, -funroll-loops, -march=native, -mtune=native, -lpthread.

Cada instância foi executada três vezes para se obter a média aritmética dos resultados e dos tempos.

#### Mcclure

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-ils-mcclure.png)

A tabela 4.16 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $ils_1$ que contém o valor encontrado pelo ILS
usando o algoritmo de solução inicial 1, a coluna $ils_2$ que contém o valor encontrado
pelo ILS usando o algoritmo de solução inicial 2, a coluna $ils_3$ que contém o valor
encontrado pelo ILS usando o algoritmo de solução inicial 3, a coluna $ils_4$ que contém
o valor encontrado pelo ILS usando o algoritmo de solução inicia![g](https://github.com/user-attachments/assets/bfa6dd3d-1f94-44e7-a3c1-911183625e54)
l 4, a coluna $lb$
com o lower bound da solução ótima, a coluna $ub$ com o upper bound da solução
ótima, a coluna $ER$ com o erro relativo entre o lower bound e a melhor resposta
entre as versões do ILS e a coluna σ com o desvio padrão entre as respostas das
versões do ILS. Além disso, o símbolo * indica quais das instâncias em que se foi
possível alcançar a solução ótima.

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-ils-time-mcclure.png)

A tabela 4.17 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $ils_1$ que contém o tempo em segundos da execução
do ILS usando o algoritmo de solução inicial 1 sobre a instância, a coluna $ils_2$ que
contém o tempo em segundos da execução do ILS usando o algoritmo de solução
inicial 2 sobre a instância, a coluna $ils_3$ que contém o tempo em segundos da execução
do ILS usando o algoritmo de solução inicial 3 sobre a instância e a coluna $ils_4$ que
contém o tempo em segundos da execução do ILS usando o algoritmo de solução
inicial 4 sobre a instância.

#### Hufsky

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-ils-hufsky.png)

A tabela 4.18 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $ils_1$ que contém o valor encontrado pelo ILS
usando o algoritmo de solução inicial 1, a coluna $ils_2$ que contém o valor encontrado
pelo ILS usando o algoritmo de solução inicial 2, a coluna $ils_3$ que contém o valor
encontrado pelo ILS usando o algoritmo de solução inicial 3, a coluna $ils_4$ que contém
o valor encontrado pelo ILS usando o algoritmo de solução inicial 4, a coluna $lb$
com o lower bound da solução ótima, a coluna $ub$ com o upper bound da solução
ótima, a coluna $ER$ com o erro relativo entre o lower bound e a melhor resposta
entre as versões do ILS e a coluna σ com o desvio padrão entre as respostas das
versões do ILS. Além disso, o símbolo * indica quais das instâncias em que se foi
possível alcançar a solução ótima.

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-ils-time-hufsky.png)

A tabela 4.19 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $ils_1$ que contém o tempo em segundos da execução
do ILS usando o algoritmo de solução inicial 1 sobre a instância, a coluna $ils_2$ que
contém o tempo em segundos da execução do ILS usando o algoritmo de solução
inicial 2 sobre a instância, a coluna $ils_3$ que contém o tempo em segundos da execução
do ILS usando o algoritmo de solução inicial 3 sobre a instância e a coluna $ils_4$ que
contém o tempo em segundos da execução do ILS usando o algoritmo de solução
inicial 4 sobre a instância.

#### Chimani

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-ils-chimani.png)

A tabela 4.20 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $ils_1$ que contém o valor encontrado pelo ILS
usando o algoritmo de solução inicial 1, a coluna $ils_2$ que contém o valor encontrado
pelo ILS usando o algoritmo de solução inicial 2, a coluna $ils_3$ que contém o valor
encontrado pelo ILS usando o algoritmo de solução inicial 3, a coluna $ils_4$ que contém
o valor encontrado pelo ILS usando o algoritmo de solução inicial 4, a coluna $lb$
com o lower bound da solução ótima, a coluna $ub$ com o upper bound da solução
ótima, a coluna $ER$ com o erro relativo entre o lower bound e a melhor resposta
entre as versões do ILS e a coluna σ com o desvio padrão entre as respostas das
versões do ILS. Além disso, o símbolo * indica quais das instâncias em que se foi
possível alcançar a solução ótima.

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-ils-time-chimani.png)

A tabela 4.21 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna $ils_1$ que contém o tempo em segundos da execução
do ILS usando o algoritmo de solução inicial 1 sobre a instância, a coluna $ils_2$ que
contém o tempo em segundos da execução do ILS usando o algoritmo de solução
inicial 2 sobre a instância, a coluna $ils_3$ que contém o tempo em segundos da execução
do ILS usando o algoritmo de solução inicial 3 sobre a instância e a coluna $ils_4$ que
contém o tempo em segundos da execução do ILS usando o algoritmo de solução inicial 4 sobre a instância.


## GA (/ga)
A abordagem utilizada é inspirada no Algoritmo Genético (GA) de (FESTA;
PARDALOS, 2012) que consiste em trabalhar com uma população dividida em três
camadas a cada geração: a elite que possui as melhores soluções, a mediana que
possui as melhores soluções que não estão na elite e que é preenchida por strings
obtidas pelo crossover e a baixa que contém a parcela restante composta por strings
aleatórias.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/g.png)
	
### Parâmetros
* $\lambda$ = $\frac{\sqrt{m}}{m}$
* $populacao$ = $|S|$
* $elite$ = 0.3
* $media$ = 0.5
* $baixa$ = 0.2

### Solução Inicial
Algorimo de solução inicial 1

### Seleção
Cada indivíduo $t$ da geração corrente recebe um número aleatório entre 0 e
$max_{1 \le i \le n} {d(t,S_i)}$ e com isso são ordenados em ordem decrescente por esse valor.
Após isso as melhores 2 ∗ $media$ soluções formam pares de tal forma que a 1ª pareia
com a 2ª, a 3 ª com a 4ª e assim em diante e com isso essas duas strings realizam
um crossover.

### Crossover
O crossover entre dois indivíduos ao contrário do que é comumente adotado,
a divisão da string em duas partes e a intercalação, adotamos uma divisão entre
subconjuntos pelo fato dos caracteres serem independentes entre si, ou seja, um
caractere não afeta na contribuição de outro na distância de hamming.
Com isso, o crossover se resume em selecionar um subconjunto de posições de
cada string de tal forma que sejam disjuntos e a união seja {1, 2, 3, ..., $m$} e usar os
elementos que estão nas posições selecionadas para gerar a nova solução.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/selecao.png)

A permutação {1,2,3, ..., $m$} é embaralhada aleatoriamente e atribuída à
pos (linha 1), um valor inteiro aleatório entre [1, $m$] é atribuído à variável quantidade
(linha 2), $u$ é inicializado como $t$ (linha 3) e quantidade posições são atribuidas à u
provenientes de $s$.

### Mutação
A mutação utilizada foi proposta em (COLEY, 1999) e ocorre individualmente em
cada posição da string de acordo com uma probabilidade $\lambda$ = $\frac{\sqrt{m}}{m}$ baixa e constante e caracteriza-se como uma mudança entre caracteres feita de forma aleatória.

![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/muta%C3%A7%C3%A3o.png)

O valor real aleatório entre [0, 1] é selecionado (linha 2), $S_i$ recebe um caractere aleatório de $\Sigma^{'}$ que é a coleção de todos os caracteres da coluna $j$ (linha 3).

### Experimentos

Os testes foram realizados em um computador rodando o Ubuntu 18.04.3 LTS, com um processador Intel Core i7-3770 com CPU 3.40GHz e memória de 8Gb, a linguagem de programação utilizada foi a C++ versão 17, o compilador foi o g++ 7.4.0 e as flags de compilação usadas foram: -O3, -funroll-loops, -march=native, -mtune=native, -lpthread.

Cada instância foi executada três vezes para se obter a média aritmética dos resultados e dos tempos.

#### Mcclure
![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-ga-mcclure.png)

A tabela 4.22 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna ga com a resposta encontrada pelo GA, a coluna
t com o tempo em segundos da execução do algoritmo sobre a instância, coluna $lb$
com o lower bound da solução ótima, a coluna $ub$ com o upper bound da solução
ótima e a coluna $ER$ com o erro relativo entre o lower bound e a resposta do GA.


#### Hufsky
![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-ga-hufsky.png)

A tabela 4.23 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna ga com a resposta encontrada pelo GA, a coluna
t com o tempo em segundos da execução do algoritmo sobre a instância, coluna $lb$
com o lower bound da solução ótima, a coluna $ub$ com o upper bound da solução
ótima e a coluna $ER$ com o erro relativo entre o lower bound e a resposta do GA.

#### Chimani

![Tabela](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/Dados/Imagens/t-ga-chimani.png)

A tabela 4.24 apresenta uma coluna instância que possui os nomes dos arquivos
com os dados da entrada, a coluna ga com a resposta encontrada pelo GA, a coluna
t com o tempo em segundos da execução do algoritmo sobre a instância, coluna $lb$
com o lower bound da solução ótima, a coluna $ub$ com o upper bound da solução
ótima e a coluna $ER$ com o erro relativo entre o lower bound e a resposta do GA.

[^1] BOUCHER, C. Closest string with outliers. BMC Bioinformatics, v. 12, p.
1471–2105, 02 2011.

[^2] CHIMANI WOSTE, B. A closer look at the closest string and closest substring
problem. ALENEX 11: Proceedings of the Meeting on Algorithm Engineering &
Expermiments, Society for Industrial and Applied Mathematics, p. 13–24, 2011.

[^3] COLEY, D. A. An Introduction to Genetic Algorithms for Scientists and Engineers.
 1. ed. [S.l.]: World Scientific Publishing Co. Pte. Ltd, 1999.

[^4] FESTA, P.; PARDALOS, P. Efficient solutions for the far from most string problem.
Ann Oper Res, v. 196, p. 663–682, 2012.

[^5] FRANCES, M.; LITMAN, A. On covering problems of codes. Theory of Computing
Systems, v. 30(2), p. 113–119, 1997.

[^6] HUFSKY, F. et al. Swiftly computing center strings. LNBI, Spring, v. 6293, p.
325–336, 2010.

[^7] KIRKPATRICK, S.; GELATT, C.; VECCHI, M. Optimization by simulated
annealing. Science (New York, N.Y.), v. 220, p. 671–80, 06 1983.

[^8] LI, M.; MA, B.; WANG, L. On The Closest String and Substring Problems. arXiv,
2000. Disponível em: <https://arxiv.org/abs/cs/0002012>.

[^9] MCCLURE MARCELLA, A.; VASI, T.; FITCH WALTER, M. Comparative
analysis of multiple protein-sequence alignment methods. Molecular biology and
evolution, v. 11 4, p. 571–92, 1994.

[^10] METROPOLIS, N. et al. Equation of state calculations by fast computing machines.
Journal of Chemical Physics, v. 21, p. 1087–1092, June 1953.

[^11] REINSMA PUCA HUACHI VAZ PENNA, M. J. F. S. J. Um algoritmo simples e
eficiente para resolução do problema do caixeiro viajante generalizado. L SIMPóSIO
BRASILEIRO DE PESQUISA OPERACIONAL, 2018.

[^12] SANTOS, A. F. M. Algoritmos heurísticos para a solução do Problema da Cadeia de
Caracteres Mais Próxima. Dissertação (Mestrado) — CEFET-MG, 2018.

[^13] SOUZA, M. J. F. Inteligência Computacional para Otimização. [S.l.], 2006.
Disponível em: <http://www.decom.ufop.br/prof/marcone/Disciplinas/
InteligenciaComputacional/SA.PPT>.
