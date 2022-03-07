#include "func.h"
#include <math.h>
#include <complex.h>
#include <string.h>

//tipo utilizado para unir as magnitudes dos coeficientes aos seus index originais
typedef struct {
	double magnitude;
	int original_index;
} Dataset;

void mergeSort(Dataset** vetor, int inicio, int fim);
void intercala(Dataset** vetor, int inicio, int centro, int fim);

void mergeSort(Dataset** vetor, int inicio, int fim){
	//caso base
	if (fim <= inicio) return;

	//processo de divis�o
	int centro = (int)((inicio+fim)/2.0);
	mergeSort(vetor, inicio, centro);
	mergeSort(vetor, centro+1, fim);

	//processo de conquista
	intercala(vetor, inicio, centro, fim);
}

void intercala(Dataset** vetor, int inicio, int centro, int fim){
	
	//intercalação
	Dataset** vetorAux = (Dataset**)malloc(sizeof(Dataset*) * (fim-inicio)+1);
	for(int a = 0; a < fim-inicio+1; a++){
		vetorAux[a] = (Dataset*) malloc(sizeof(Dataset));
	}
	int i = inicio;	// indice da primeira lista ordenada
	int j = centro+1; //indice da segunda lista ordenada
	int k = 0; //indice do vetor auxiliar
	
	//compara e intercala os elementos do menor para o maior
	while(i <= centro && j <= fim){
		if (vetor[i]->magnitude >= vetor[j]->magnitude){ //verifica qual é o elemento com maior magnitude entre as duas listas
			vetorAux[k]->magnitude = vetor[i]->magnitude;
			vetorAux[k]->original_index = vetor[i]->original_index;
			i++; //proximo elemento da primeira metade
		}
		else{
			vetorAux[k]->magnitude = vetor[j]->magnitude;
			vetorAux[k]->original_index = vetor[j]->original_index;
			j++; //proximo elemento da segunda metade
		}
		k++;
	}

	while(i <= centro){//há elementos na primeira metade ainda?
		vetorAux[k]->magnitude = vetor[i]->magnitude;
		vetorAux[k]->original_index = vetor[i]->original_index;
		i++;
		k++;
	}

	while(j <= fim){//há elementos na segunda metade ainda?
		vetorAux[k]->magnitude = vetor[j]->magnitude;
		vetorAux[k]->original_index = vetor[j]->original_index;
		j++;
		k++;
	}

	//atualizando o vetor original com o vetor auxiliar(ordenado)
	for(i = inicio, k = 0; i <= fim; i++,k++) {
		vetor[i]->magnitude = vetorAux[k]->magnitude;
		vetor[i]->original_index = vetorAux[k]->original_index;
	}
	for(int a = 0; a < fim-inicio; a++){
		free(vetorAux[a]);
	}
}

// função para calcular magnitude dos coeficientes complexos
double magnitude(double complex complex_number){
    double module = pow(creal(complex_number),2) + pow(cimag(complex_number),2);
	double result = sqrt(module);
    return result;    
}

int main(){

    char filename[20];
    int n_coefficients = 0;
    
    scanf("%s", filename);
    scanf("%d", &n_coefficients);

	// le dados do arquivo de audio e mede o tamanho da leitura
    unsigned char* file_data =  read_wav_data(filename);
	int file_data_size = strlen((const char* ) file_data);
	printf("%d\n", file_data_size);
	
	//le cabecalho do Arquivo de entrada
	FILE* fr = fopen(filename, "r+");
	char header[44];
	fread(header, sizeof(char), 44, fr);

	// escreve cabeçalho no arquivo de saida
	FILE* fw = fopen("out.wav", "w+");
	fwrite(header, sizeof(char), 44, fw);

	//transforma os dados pela função de Transformada de Fourier
    double complex* coefficients = DFT(file_data, file_data_size);

	Dataset** dataset = (Dataset**) malloc(sizeof(Dataset*)*file_data_size);
	int cont = 0;

	for(int i = 0; i < file_data_size; i++) {

		//conta quantos coeficientes não tem nenhuma parte <= 0
		if(creal(coefficients[i]) <= 0.0 && cimag(coefficients[i]) <= 0.0) { 
			cont++;
		} 
		
		//salva magnitudes calculadas e respectiva posição do coeficiente
		dataset[i] = (Dataset*) malloc(sizeof(Dataset));
		dataset[i]->magnitude = magnitude(coefficients[i]);
		dataset[i]->original_index = i;

    }

	//printa contagem de coeficientes com ambas as partes menores que 0
	printf("%d\n", cont);

	//ordena as magnitudes
    mergeSort(dataset, 0, file_data_size-1);
	
	//zera as magnitudes, exceto as T primeiras 
	for(int i = n_coefficients; i < file_data_size; i++) { 
		coefficients[dataset[i]->original_index] = 0;
	}

	// faz a transformada inversa e guarda os coeficientes
	unsigned char* reverse_coefficients = RFT(coefficients, file_data_size);
	
	// escreve os coeficientes no arquivo de saida
	for(int i = 0; i < file_data_size; i++) {
		fwrite(&reverse_coefficients[i], sizeof(unsigned char), 1,fw);
	}

	// printa as T primeiras magnitudes
	for(int i = 0; i < n_coefficients; i++) {
		printf("%d\n", (int) dataset[i]->magnitude);
	}
	
	// desaloca memória
	for(int i = 0; i < file_data_size; i++) { 
		free(dataset[i]);
	}
	
	fclose(fw);
	fclose(fr);
    
	return 0;
}
