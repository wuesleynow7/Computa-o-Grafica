#include<stdio.h>

#include<stdlib.h>

typedef struct image{

    int largura;
    int altura;
    int** red;
    int** green;
    int** blue;

} image;

image* inicializa(image* imagem,int largura, int altura){

    int i,j;
    imagem->altura=altura;
    imagem->largura=largura;

    imagem->red = (int **)malloc( altura * sizeof(int *));

    for (i=0; i<altura; i++) {
        imagem->red[i] = (int *)malloc(largura * sizeof(int));
    }
    imagem->green = (int **)malloc(altura * sizeof(int *));

    for (i=0; i<altura; i++) {
        imagem->green[i] = (int *)malloc(largura * sizeof(int));
    }
    imagem->blue = (int **)malloc(altura * sizeof(int *));
    for (i=0; i<altura; i++) {
        imagem->blue[i] = (int *)malloc(largura * sizeof(int));
    }
    for (i = 0; i < imagem->altura; i++)
        for (j = 0; j < imagem->largura; j++){

        // só as 3 cores gera uma imagem sólida
        imagem->red[i][j] = 0;
        imagem->green[i][j] = 0;
        imagem->blue[i][j] = 0;

        // para fazer o arco iris ou cores separadas tem que mudar de altura ou largura, se nao todas as cores serao sobrepostas
        // if(i< 20){
        //     imagem->red[i][j] = 2;
        //     imagem->green[i][j] = 127;
        //     imagem->blue[i][j] = 99;
        // }
        // else if(i < 40){
        //     imagem->red[i][j] = 255;
        //     imagem->green[i][j] = 0;
        //     imagem->blue[i][j] = 200;
        // }
        //         else if(i < 300){
        //     imagem->red[i][j] = 255;
        //     imagem->green[i][j] = 255;
        //     imagem->blue[i][j] = 200;
        // }
        //         else if(i < 400){
        //     imagem->red[i][j] = 255;
        //     imagem->green[i][j] = 0;
        //     imagem->blue[i][j] = 255;
        // }
    }
return imagem;
}

image* salvaImagem(image* imagem, const char* nomeDoArquivo){

    FILE* arquivo;
    arquivo = fopen(nomeDoArquivo,"wt");

    if (arquivo == NULL) {
        return NULL;
    }

    int i,j;
    fprintf(arquivo, "P3\n%d %d\n255\n", imagem->largura, imagem->altura);

    for (i = 0; i < imagem->altura; i++){
        for (j = 0; j < imagem->largura; j++){
            fprintf(arquivo, "%d %d %d ", imagem->red[i][j], imagem->green[i][j], imagem->blue[i][j]);
    }
    fprintf(arquivo, "\n");
    }
    fclose(arquivo);
    return imagem;
}

void putPixel(image* figura, int coordenada_x, int coordenada_y, int r, int g, int b){
/*O que ela deve fazer: dado um ponteiro pra imagem, uma coordenada (x,y) e três valores de cor (r,g,b),
 escrever essa cor na posição indicada, sem sair dos limites da matriz alocada.*/

    if (coordenada_x >= 0 && coordenada_x < figura->altura && coordenada_y >= 0 && coordenada_y < figura->largura){
        //defini a cor que vai em cada matriz e a posicao 
        figura->red[coordenada_x][coordenada_y]   = r;
        figura->green[coordenada_x][coordenada_y] = g;
        figura->blue[coordenada_x][coordenada_y]  = b;
    }   
    else{
        // fora dos limites: pixel ignorado silenciosamente "coordenada fora dos limites da imagem [undefined behavior / corrupção de memória]"
    }
}

int get_red(image* figura, int x, int y){

    if (x >= 0 && x < figura->altura && y >= 0 && y < figura->largura){
        return figura->red[x][y];
    }
    else{
        return -1;
    }
}

int get_blue(image* figura, int x, int y){

    if (x >= 0 && x < figura->altura && y >= 0 && y < figura->largura){
        return figura->blue[x][y];
    }
    else{
        return -1;
    }
}

int get_green(image* figura, int x, int y){

    if (x >= 0 && x < figura->altura && y >= 0 && y < figura->largura){
        return figura->green[x][y];
    }
    else{
        return -1;
    }

}

void set_pixel(image* figura, int coordenada_x, int coordenada_y, int r, int g, int b){
    // função que
    /// irá definir a cor de um pixel dadas as suas coordenadas na imagem e as
    /// intensidades de suas componentes vermelha, verde e azul.
    if (coordenada_x>= 0 && coordenada_x < figura->altura && coordenada_y >=0 && coordenada_y < figura->largura)
    {
        figura->red[coordenada_x][coordenada_y]   = r;
        figura->green[coordenada_x][coordenada_y] = g;
        figura->blue[coordenada_x][coordenada_y]  = b;
    }
    else{
        printf("coordenada fora dos limites da imagem [undefined behavior / corrupção de memória]");
    }
}






void floodfill(image* imagem, int x, int y,int rold, int gold, int bold, int rfill, int gfill, int bfill){

    //pega a coordenada 
    int cr = get_red (imagem,x,y);
    int cg = get_green(imagem,x,y);
    int cb = get_blue(imagem,x,y);

    if(cr == rold && cg == gold && cb == bold){

        // alterar
        set_pixel(imagem,x,y,rfill, gfill, bfill);

        //só vai para o proximo floodfill se 
        floodfill(imagem,x+1,y,rold, gold, bold,rfill, gfill, bfill);
        floodfill(imagem,x-1,y,rold, gold, bold,rfill, gfill, bfill);
        floodfill(imagem,x, y+1,rold, gold, bold,rfill, gfill, bfill);
        floodfill(imagem,x,y-1,rold, gold, bold,rfill, gfill, bfill);
    }
}

//floodfill iterativo é o correto, pois não estoura a pilha
// void floodfill_iterativo(){

//     //cor original é a cor de fundo
//     if (cor_original == cor_nova){


        
//     }
    

// }

int sgn(int v) {
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

void drawline(image* figura, int x1, int y1, int x2, int y2, int r, int g, int b){

    int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;
    
    dx=x2-x1;      /* the horizontal distance of the line */// diferença distancia final e inicial como se fosse uma vetor
    dy=y2-y1;      /* the vertical distance of the line */

    //modulo da distancia
    dxabs=abs(dx);
    dyabs=abs(dy);

    //
    sdx=sgn(dx);
    sdy=sgn(dy);

    //
    x=dyabs>>1;
    y=dxabs>>1;
    px=x1;
    py=y1;

    /* the line is more horizontal than vertical */
    if (dxabs>=dyabs){
        for(i=0; i<dxabs; i++){

            y+=dyabs;
            if (y>=dxabs){
                y-=dxabs;
                py+=sdy;
            }
            px+=sdx;
            
            putPixel(figura,px,py,r,g,b);

        }
    }
    else /* the line is more vertical than horizontal */{
        for(i=0; i<dyabs; i++){

            x+=dxabs;
            if (x>=dyabs){
                x-=dyabs;
                px+=sdx;
            }
            py+=sdy;
            putPixel(figura,px,py,r,g,b);
			
        }
    }
}

// https://www.youtube.com/watch?v=CceepU1vIKo

// https://www.youtube.com/watch?v=t7Ztio8cwqM





int main(){
    return 0;
}