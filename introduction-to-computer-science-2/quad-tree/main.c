#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int** values;
    int* sizes;
} QuadTree;

//o certo seria passar um tamanho de profundidade máxima baseada no tamanho da imagem
//porém esse tamanho sempre vai ser mais que o suficiente
QuadTree* createQuadTree(int tree_size) {
    
    QuadTree* tree = (QuadTree*) malloc(sizeof(QuadTree));
    tree->sizes = (int*) malloc(sizeof(int));
    tree->values = (int**) malloc(sizeof(int*)*tree_size);
    
    for(int i = 0; i < tree_size; i++) {
        tree->values[i] = (int*) malloc(sizeof(int));
    }

    return tree;
}

QuadTree* append(QuadTree *tree, int tree_level, int value) {
    tree->sizes[tree_level]++; 
    tree->values[tree_level] = realloc(tree->values[tree_level], sizeof(int)*tree->sizes[tree_level]);
    tree->values[tree_level][tree->sizes[tree_level]-1] = value;

    return tree;
}

int divide(int** image, int inicioX, int fimX, int inicioY, int fimY, QuadTree* quadTree, int image_size) {
    
    //profundidade na árvore(cima para baixo)
    int tree_level = image_size/((fimX - inicioX)+1) - 1;
       
    //caso base - é um elemento
    if (fimX == inicioX && fimY == inicioY) {
        int value = image[inicioX][inicioY];
        return value;
    }
    
    //faz a divisão
    int centroX = (int)((inicioX+fimX)/2.0);
    int centroY = (int)((inicioY+fimY)/2.0);
    
    //percorre os quadrantes
    int* values = (int*) malloc(sizeof(int)*4);    
    values[0] = divide(image, inicioX, centroX, inicioY, centroY, quadTree, image_size);
    values[1] = divide(image, inicioX, centroX, centroY+1, fimY, quadTree, image_size);
    values[2] = divide(image, centroX+1, fimX, inicioY, centroY, quadTree, image_size);
    values[3] = divide(image, centroX+1, fimX, centroY+1, fimY, quadTree, image_size);
    
    int value = 0;
    //mesmo valor
    if(
        values[0] == values[1] &&
        values[1] == values[2] &&
        values[2] == values[3]) {
        
        //salva apenas o valor resumido        
        value = values[0];

    }
    //valores diferentes
    else {
        
        //salva cada um na árvore
        for(int i = 0; i < 4; i++) {
            append(quadTree, tree_level+1, values[i]);
        }
        
        value = -1;
    }

    free(values);
    
    return value;
	
}

void printTree(QuadTree* tree, int level, int index) {
    
    if(index >= tree->sizes[level]) return;
    
    if(tree->values[level][index] == -1) {
        printf("-1 ");
        for(int i = 0; i < 4; i++) {
            printTree(tree, level+1, i);
            
            tree->values[level+1][i] = tree->values[level+1][i+4];
        }
        
        return;
    }
    printf("%d ", tree->values[level][index]);
 
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
            scanf("%d", &image[i][j]);
        }
    }


    QuadTree* tree = createQuadTree(m);
    divide(image, 0, m-1, 0, n-1, tree, m);
    append(tree, 0, -1);
    
    printTree(tree, 0, 0);

    free(tree);
    return 0;
}