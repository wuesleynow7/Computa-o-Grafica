#include<stdio.h>
#include<stdlib.h>

/*
🧪 Exercício 1 — Entendendo endereços

Tarefa:
Crie duas variáveis int a e int b.
Crie dois ponteiros p1 e p2 e faça com que:

p1 aponte para a

p2 aponte para b

Depois:

use *p1 para colocar 10 em a

use *p2 para colocar 20 em b

imprima o valor de a, b, *p1, *p2, p1 e p2

💡 Dica:
Tente entender o que muda entre imprimir p1 (endereço) e *p1 (conteúdo).
*/

int main(){

    int a, b;
    int *Ponteiro1, *Ponteiro2;

    Ponteiro1 = &a; // o Ponteiro1 recebe o endereco de a, ponteiros guardam enderecos apenas
    Ponteiro2 = &b; // o Ponteiro2 recebe o endereco de b, ponteiros guardam enderecos apenas


    *Ponteiro1 = 10; // o conteudo que vamos colocar no endereco que o Ponteiro1 aponta que eh o a é 10
    *Ponteiro2 = 20; // o conteudo que vamos colocar no endereco que o Ponteiro2 aponta que eh o a é 20

    printf("o valor de a eh: %d \n",a);
    printf("o endereco de a eh: %p \n",&a);
    printf("o valor de b eh: %d \n",b);
    printf("o endereco de b eh: %p \n",&b);
    printf("o valor apontado pelo Ponteiro1 eh: %d \n",*Ponteiro1);
    printf("o valor de a eh: %d \n",*Ponteiro2);
    printf("o endereco de a eh: %p \n", (void*)&a);
    printf("o endereco de b eh: %p \n", (void*)&b);

}