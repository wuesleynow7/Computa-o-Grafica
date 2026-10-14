#include<stdio.h>
#include<stdlib.h>

/*
🧪 Exercício 3 — Alocação dinâmica simples

Tarefa:
Crie um ponteiro int* v e use malloc para alocar espaço para 5 inteiros.
Peça para o usuário digitar 5 valores, armazene em v e depois imprima todos.

💡 Dica:
Você vai precisar usar v[i] = ... e lembrar de free(v) no final.
O malloc devolve o endereço da “primeira casa” do vetor.
*/



int main(){

    // primeiro fazemos...
    // Alocamos dinamicamente espaço para 5 inteiros na memória
    int* vetor = (int*) malloc(5 * sizeof(int)); // malloc devolve o ENDEREÇO da primeira posição do vetor
    

    printf("digite 5 valores: \n");

    for(int i=0; i<5;i++){
        scanf("%d",&vetor[i]); // &vetor[i] = endereço da i-ésima posição
    }

    printf("os 5 valores sao: ");
    for(int i=0; i<5;i++){
        printf("%d ", vetor[i]); // vetor[i] acessa o conteúdo da i-ésima posição
    }

   
    free(vetor);
    // Libera a memória que malloc reservou

    return 0;
}