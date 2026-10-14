#include <stdio.h>
#include <math.h>
#include <stdlib.h>


typedef struct image{

    int largura;
    int altura;
    int** red;
    int** green;
    int** blue;

} image;

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



void cls(){
  printf("\x1b[H");
}
int sgn(int x){
	if (x<0)return -1;else return 1;
}

void locate(int x, int y){
	
    printf("\x1b[%i;%iH",y,x);
		
}
void fgrgb(int r, int g, int b){
	
	 printf("\033[38;2;%i;%i;%im",r,g,b);
}

void fg(int n){
	
	 printf("\033[38;5;%im",n);
}

void bgrgb(int r, int g, int b){
	
	 printf("\033[48;2;%i;%i;%im",r,g,b);
}
void bg(int n){
	
	 printf("\033[48;5;%im",n);
}

void drawline(int x1, int y1, int x2, int y2, int fore, int back, int c)
{
    int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;
    char chars[4]={176,177,178,219};
    dx=x2-x1;      /* the horizontal distance of the line */
    dy=y2-y1;      /* the vertical distance of the line */
    dxabs=abs(dx);
    dyabs=abs(dy);
    sdx=sgn(dx);
    sdy=sgn(dy);
    x=dyabs>>1;
    y=dxabs>>1;
    px=x1;
    py=y1;

    if (dxabs>=dyabs) /* the line is more horizontal than vertical */
    {
        for(i=0; i<dxabs; i++)
        {
            y+=dyabs;
            if (y>=dxabs)
            {
                y-=dxabs;
                py+=sdy;
            }
            px+=sdx;
            locate(px,py);
			fg(fore);
			bg(back);
			printf("%c",chars[c]);
        }
    }
    else /* the line is more vertical than horizontal */
    {
        for(i=0; i<dyabs; i++)
        {
            x+=dxabs;
            if (x>=dyabs)
            {
                x-=dyabs;
                px+=sdx;
            }
            py+=sdy;
            locate(px,py);
			fg(fore);
			bg(back);
			printf("%c",chars[c]);
        }
    }
}



int main(){

   //tenho que criar a imagem na memoria e inicializar ela
   image* quadrado = malloc(sizeof *quadrado);
   quadrado = inicializa(quadrado, 100, 100);


    int i;
	char chars[4]={176,177,178,219};

	cls();
    
	for (i=0;i<9;i++){fg(i);printf("%c",chars[3]); }
	for (i=0;i<40;i++){
		drawline(0,i,150,i,4,4,3);
	}
	for (i=40;i<50;i++){
		drawline(0,i,150,i,2,2,3);
	}
		
	for (i=10;i<25;i++){
		drawline(50.0-30.0*sin(((double)i-10)/15.0*3.1415),i-9,50.0+20.0*sin(((double)i-10)/15.0*3.1415),i-9,7,7,3);
	}	
		
	for (i=10;i<25;i++){
		drawline(30.0-20.0*sin(((double)i-10)/15.0*3.1415),i,30.0+20.0*sin(((double)i-10)/15.0*3.1415),i,2,2,3);
	}
    
	drawline(28,20,28,42,1,0,1);
	drawline(29,20,29,42,1,0,1);
	drawline(30,20,30,42,1,1,3);
	drawline(31,20,31,42,1,1,3);
	drawline(32,20,32,42,7,1,1);
	drawline(33,20,33,42,7,1,1);

	// for (i=10;i<25;i++){
	// 	drawline(90.0-10.0*sin(((double)i-10)/15.0*3.1415),i-5,90.0+10.0*sin(((double)i-10)/15.0*3.1415),i-5,3,3,3);
	// }

}