#include <stdio.h>
#include <stdlib.h>

// void divide(image, m, n) {
    
// }


// valores(image, m, n) {

// }

int divide(int** image, int inicioX, int fimX, int inicioY, int fimY) {
    // printf("%d %d %d %d ", inicioX, fimX, inicioY, fimY);
    
    //caso base - é um elemento
    if (fimX == inicioX && fimY == inicioY) {
        return image[inicioX][inicioY];
    }
    
    //faz a divisão
    int centroX = (int)((inicioX+fimX)/2.0);
    int centroY = (int)((inicioY+fimY)/2.0);
    // printf("mid: %d %d\n", centroX, centroY);
    int* values = (int*) malloc(sizeof(int)*4);    
    values[0] = divide(image, inicioX, centroX, inicioY, centroY);
    values[1] = divide(image, inicioX, centroX, centroY+1, fimY);
    values[2] = divide(image, centroX+1, fimX, inicioY, centroY);
    values[3] = divide(image, centroX+1, fimX, centroY+1, fimY);
    
    int value = 0;
    //mesmo valor
    if(
        values[0] == values[1] &&
        values[1] == values[2] &&
        values[2] == values[3]) {
        value = values[0];
        // printf("%d", value);
    }
    //valores diferentes
    else {
        value = -1;
        // printf("%d", value);
        printf("%d", values[0]);
        printf("%d", values[1]);
        printf("%d", values[2]);
        printf("%d", values[3]);
    }
    free(values);
    
    return value;
	//faz a conquista
	// intercala(vetor, inicio, centro, fim);
}

int main(){
    
    //reads matrix size
    int m, n;
    scanf("%d %d",&m, &n);

    int** image = (int**) malloc (sizeof(int*) *m);
    for(int i = 0; i < m; i++){
        image[i] = (int*) malloc (sizeof(int) *n);
    }
    
   
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++) {
            // printf("%d", image[i][j]);
            scanf("%d", &image[i][j]);
        }
    }

    int* vetor = malloc(sizeof(int));

    divide(image, 0, m-1, 0, n-1);
    
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++) {
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }
    return 0;
}