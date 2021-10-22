/*
Prova 1 - ICC 2 - 7/10/21

Abimael Alves de Oliveira Neto - 10747822
Questão 1

FUNÇÕES MERGESORT E INTERCALAÇÃO CRIADAS PELOS PROFESSORES MOACIR E FERNANDO
OBS: Entendi que não teria muito ganho em analisar formas de implementar o algoritmo mergeSort, e sim a maneira de chamá-lo
*/

#include <stdio.h>
#include <stdlib.h>

void intercala(int* vetor, int inicio, int centro, int fim);

void imprimeVetor(int* vetor, int tamanho){
	int i;
	printf("Vetor: ");
	for (i=0; i<tamanho; i++) printf("%i ", vetor[i]);
	printf("\n");
}

int** alloc_matrix(int m) {
	int **mat = malloc(sizeof(int*)*m);
	srand(m);
	
	int in = 0;
	// aloca matriz ordenada
	for (int i = 0; i < m; i++) {
		mat[i] = malloc(sizeof(int)*m);
	    	for (int j = 0; j < m; j++) {
			if (i == j) in+= (rand()%3)+1;
			else in += rand()%3;
			mat[i][j] = in;
		}
	}
	// desordena matriz triangular superior
	for (int i = 0; i < m-2; i++) {
	    	for (int j = i+1; j < m-1; j++) {
			int swaps = (int)((m-j)/2.0)+1;
			for (int t = 1; t <= swaps; t++) {
				int a = (rand()%(m-j))+j;
				int b = (rand()%(m-j))+j;
				int tmp = mat[i][a];
				mat[i][a] = mat[i][b];
				mat[i][b] = tmp;
			}
		}

	}
	return mat;
}

// algoritmo merge sort padrão
void mergeSort(int* vetor, int inicio, int fim) {
    if (fim <= inicio) return; // c

	//parte de divisão
	int centro = (int)((inicio+fim)/2.0); // 2a
	mergeSort(vetor, inicio, centro); // m(n/2)
	mergeSort(vetor, centro+1, fim); // a + m(n/2)

	//parte de conquista
	intercala(vetor, inicio, centro, fim); // i(n)
}
/* 
Merge sort:

m(n) = c + 2a + 2m(n/2) + a + i(n)
= (c + 3a) + i(n) + 2m(n/2)
sabemos que i(n) = 2a + (c+4a)n
assim:

m(n) = (c + 3a) + 2a + (c+4a)n + 2m(n/2)
= (c+5a) + (c+4a)n + 2m(n/2)
= (c+5a) + (c+4a)n + (c+5a) + (c+4a)n + 2m(n/4))

generalizando, temos:

m(n) = k*((c+5a) + (c+4a)n) + 2^(k)*(m(n/2^k))

para o caso base, m(1)=c e k = logn (base2)
m(n) = logn (base2)*((c+5a) + (c+4a)n)+ 2^logn (base2)*c

--- m(n)= logn (base2)*((c+5a) + (c+4a)n) + n ---

COMPLEXIDADE: n.logn

*/

void intercala(int* vetor, int inicio, int centro, int fim){
	//intercalação
	int* vetorAux = (int*)malloc(sizeof(int) * (fim-inicio)+1); // a

	int i = inicio;	// indice da primeira lista ordenada
	int j = centro+1; //indice da segunda lista ordenada // a
	int k = 0; //indice do vetor auxiliar 

	//compara e intercala os elementos do menor para o maior
	while(i <= centro && j <= fim){ 
		if (vetor[i] <= vetor[j]){ //verifica qual � o elemento menor entre as duas listas // c
			vetorAux[k] = vetor[i];
			i++; //proximo elemento da primeira metade // a
		}
		else{
			vetorAux[k] = vetor[j];
			j++; //proximo elemento da segunda metade // a
		}
		k++; // a
	}

	while(i <= centro){//há elementos na primeira metade ainda? 
		vetorAux[k] = vetor[i]; 
		i++; // a
		k++; // a
	}

	while(j <= fim){//há elementos na segunda metade ainda?
		vetorAux[k] = vetor[j];
		j++; // a
		k++; // a
	}

	//atualizando o vetor original com o vetor auxiliar(ordenado)
	for(i = inicio, k = 0; i <= fim; i++,k++)
		vetor[i] = vetorAux[k];
	free(vetorAux);
}

/* 
Intercalação:

i(n) = a + a + (c+2a)n+(2a)n/2 + (2a)n/2
 = 2a + (c+4a)n
*/



int main (int argc, char* argv[]){
	int m;
	scanf("%d", &m);
	
	int vetor[m*m];
	int** matriz = alloc_matrix(m);
	
	int i, j, k = 0;
    //aloca vetor
	for (i=0; i<m; i++)
		for (j=0; j<m; j++)
			vetor[k++] = matriz[i][j];			

    for(int i = 1; i < m*m-1; i = i+m+1) {
        mergeSort(vetor, i, i+m-1);
    }
    /*
    Complexidade da main:
    - Ordena (m-1) vetores de tamanho m
    f(n) = (m-1)*m(m)
    com m(n) = logn (base2)*((c+5a) + (c+4a)n) + nc, temos:
    
    -- f(n) = (m-1)(logm (base2)*((c+5a) + (c+4a)m) + mc) --
    */

    //imprime matriz
	k = 0;
	for (i=0; i<m; i++){
		for (j=0; j<m; j++){
			matriz[i][j] = vetor[k++];
			printf("%i ", matriz[i][j]);
		}
		printf("\n");
	}

	free(matriz);

	return 0;
}
