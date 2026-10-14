#include<stdio.h>
#include<stdlib.h>

/*
🧪 Exercício 4 — Troca de valores com ponteiros

Tarefa:
Crie uma função void troca(int* x, int* y) que troca o valor de duas variáveis.
*/

void troca(int* x,int* y){
    //troca entre conteudos que os ponteiros apontam
    int aux = *x; 
    *x = *y;
    *y = aux;
}


int main(){

    int numero1 = 3;
    int numero2 = 7;

    printf("os valores antes da troca sao:  numero1 = %d, numero2 = %d \n\n", numero1, numero2);


    troca(&numero1,&numero2);

    printf("os valores trocados sao: numero1 = %d, numero2 = %d",numero1,numero2);

    return 0;
}