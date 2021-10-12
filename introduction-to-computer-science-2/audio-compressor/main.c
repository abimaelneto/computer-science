#include "func.h"
#include <math.h>
#include <complex.h>

void mergeSort(double complex* vetor, int inicio, int fim, double complex* ordered_vector);
void intercala(double complex* vetor, int inicio, int centro, int fim, double complex* ordered_vector);

double magnitude(double complex complex_number){
    double module = pow(creal(complex_number),2) + pow(cimag(complex_number),2);
    return sqrt(module);    
}

void mergeSort(double complex* vetor, int inicio, int fim, double complex* ordered_vector){
	//caso base
	if (fim <= inicio) return;

	//processo de divis�o
	int centro = (int)((inicio+fim)/2.0);
	mergeSort(vetor, inicio, centro, ordered_vector);
	mergeSort(vetor, centro+1, fim, ordered_vector);

	//processo de conquista
	intercala(vetor, inicio, centro, fim, ordered_vector);

}


void intercala(double complex* vetor, int inicio, int centro, int fim, double complex* ordered_vector){
	//intercalação
	int* vetorAux = (int*)malloc(sizeof(int) * (fim-inicio)+1);

	int i = inicio;	// indice da primeira lista ordenada
	int j = centro+1; //indice da segunda lista ordenada
	int k = 0; //indice do vetor auxiliar

	//compara e intercala os elementos do menor para o maior
	while(i <= centro && j <= fim){
		if (magnitude(vetor[i]) >= magnitude(vetor[j])){ //verifica qual é o elemento com maior magnitude entre as duas listas
			vetorAux[k] = vetor[i];
			i++; //proximo elemento da primeira metade
		}
		else{
			vetorAux[k] = vetor[j];
			j++; //proximo elemento da segunda metade
		}
		k++;
	}

	while(i <= centro){//há elementos na primeira metade ainda?
		vetorAux[k] = vetor[i];
		i++;
		k++;
	}

	while(j <= fim){//há elementos na segunda metade ainda?
		vetorAux[k] = vetor[j];
		j++;
		k++;
	}

	//atualizando o vetor original com o vetor auxiliar(ordenado)
	for(i = inicio, k = 0; i <= fim; i++,k++)
		ordered_vector[i] = vetorAux[k];
	free(vetorAux);
}


int main(){
    char filename[20];
    int n_coefficients = 0;
    
    scanf("%s", filename);
    scanf("%d", &n_coefficients);


    unsigned char* file_data =  read_wav_data(filename);

    double complex* coefficients = DFT(file_data, n_coefficients);
    double complex* ordered_coefficients = (double complex*) malloc(sizeof(double complex)* n_coefficients);
    
    mergeSort(coefficients, 0, n_coefficients-1, ordered_coefficients);


    
    for(int i = 0; i < n_coefficients; i++) {
        
        printf("%lf\n", magnitude(ordered_coefficients[i]));
    }

    for(int i = 0; i < n_coefficients; i++) {
        
        printf("%lf\n", magnitude(coefficients[i]));
    }

    return 0;
}
/*
audios/bubble.wav
*/
