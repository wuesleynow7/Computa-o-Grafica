#include<stdio.h>
#include <stdlib.h>

typedef struct image{

    int largura;
    int altura;
    int** red;
    int** green;
    int** blue;

} image;

image* filtro_miniatura(image *in){}
image* edges_sobel(image *in){}       //magnitude Sobel 
image* edges_sobel_h(image *in){}      // Sobel horizontal 
image* edges_sobel_v(image *in){}      // Sobel vertical 
image* edges_laplacian(image *in){}    // Laplaciano 3x3 
image* motion_from_edges(image *A,image *B){} // bônus

int main(){
    return 0;
}