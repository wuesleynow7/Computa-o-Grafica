#include <stdio.h>
#include <stdlib.h>

/*
 💡 Dica:
    Ponteiro é uma variavel que armazena o endereço de memória de outra variavel, que aponta para o endereço de outra variavel

*/


/*👉 Quando você passa uma variável sem ponteiro, a função recebe uma cópia do valor.
Se mudar lá dentro, fora da função continua igual.*/

void mudaNumero(int x) { //recebe uma cópia da variavel criada na main numero (não muda o original)
    x = 10;  // muda só a cópia e a variavel original permanece 5
    printf("%d\n", x);
}


/*👉 Quando você passa um ponteiro para uma função, a função recebe o endereço real da variável.
Então, se mudar lá dentro, muda também fora da função.*/

void mudaNumeroPonteiro(int* x) {// recebe o endereço da variavel numero e muda o valor real
    *x = 10; // muda o valor da casa que o ponteiro aponta
}



int main() {

    int numero = 5;

    mudaNumero(numero);
    printf("%d\n", numero); // ainda é 5

    mudaNumeroPonteiro(&numero);
    printf("%d\n", numero); // agora é 10
}




/*

#include <stdio.h>
#include <stdlib.h>

void funcaoSwap(int *valor1, int *valor2) {// a funcao recebe dois ponteiros como argumentos, ponteiros guardam endereços e ponto final
    int Auxiliar = *valor1;  // guarda o valor apontado por valor1
    *valor1 = *valor2;       // troca o valor de valor1 pelo de valor2
    *valor2 = Auxiliar;      // valor2 recebe o valor original de valor1
}
int main() {
    int val1 = 10, val2 = 3;

    printf("Antes da troca: val1 = %d, val2 = %d\n", val1, val2);

    funcaoSwap(&val1, &val2); // Passa os endereços

    printf("Depois da troca: val1 = %d, val2 = %d\n", val1, val2);

    return 0;
}


*/