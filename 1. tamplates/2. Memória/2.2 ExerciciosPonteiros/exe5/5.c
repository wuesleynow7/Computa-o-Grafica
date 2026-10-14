#include<stdio.h>
#include<stdlib.h>


/*
🧪 Exercício 5 — Estrutura com ponteiro

Tarefa:
Crie uma struct Ponto com int x, y.
Crie uma função void movePonto(struct Ponto* p, int dx, int dy)
que some dx e dy às coordenadas.

💡 Dica:
Lembre: como você passa um ponteiro, pode acessar os campos com p->x e p->y.
*/

typedef struct ponto{
    int x, y;
}Ponto;


void movePonto(Ponto* p, int dx, int dy){
    // primeiro fazemos...
    // acessamos o campo x do endereço p com "p->x"
    // e somamos o deslocamento dx ao valor atual
    p->x = p->x + dx;

    // depois fazemos...
    // o mesmo para o campo y
    p->y = p->y + dy;
}


int main(){

    Ponto ponto;
    ponto.x = 2;
    ponto.y = 3;

    int d = 4;
    int e = 5;

    movePonto(&ponto,d,e);

    printf("o valor da soma eh: dx = %d e dy = %d",ponto.x, ponto.y);

}