#include<stdio.h>
#include<stdlib.h>

/*
🧪 Exercício 2 — Função que dobra um número

Tarefa:
Crie uma função void dobra(int* x) que dobra o valor de uma variável.
No main, crie uma variável n = 5, chame dobra(&n) e depois mostre o novo valor.

💡 Dica:
Pense: a função recebe o endereço de n.
Então, para alterar o valor real, você precisa usar o operador *.
*/

/*

💡 Pensamento para fixar:

x → é o endereço (ex: 0x7ffe...)

/*x → é o valor guardado nesse endereço (ex: 5)

então, *x = *x * 2 quer dizer:
“No local onde x aponta, guarde o dobro do que estava lá.”

*/
void dobra(int* x){//recebe um endereco de uma variavel inteira
    //tenho que pegar o conteudo desse endereço e multiplicar por 2
    *x =  *x*2; //aqui estou dizendo o seguinte o conteudo de x recebe o proprio conteudo dele multiplicado por 2
    // agora o conteúdo no endereço de x é atualizado
}

int main(){

    int numero = 5;

    dobra(&numero);// passa o endereco da variavel numero

    printf("o valor dobrado eh %d\n",numero);

  
}