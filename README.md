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
1. Abra a pasta alvo e dê um ./make
2. execute ./[programa] [arquivo com as instâncias]
	
## Simulated Annealing (/sa/sa-[versão])
![Pseudocódigo](https://github.com/ThiagoFBastos/Closest-String-Problem/blob/master/SA.png)
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
	
