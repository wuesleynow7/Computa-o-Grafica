#include<iostream>
#include<stdio.h>

using namespace std;


int main(){


    /*
    ########### ATRIBUIÇÃO POR CÓPIA 

    é o caso do exemplo de código, quando atribuimos o valor a variavel A e na sequencia atribuibos a variavel A à variavel B essa é uma atribuição
    por cópia, neste cenário uma cópia do valor 2 é atribuido a B de tal forma que se mechermos no valor da variavel A e mechermos no valor de B 
    cada variavel terá seu valor independente uma nao vai interferir na outra.  
    

    ########### ATRIBUIÇÃO POR REFERÊNCIA

    Nesse caso teremos uma referencia para um local de memória onde a informação está, se compratilharmos com outra variavel significa que elas apontam
    para o mesmo local de memória, isso é perigoso pois pode acontecer alteraçoes feitas por uma variavel A  a variavel B tambem perceberá a mudança e 
    isso foi feito para, compartilharmos espaços de memória e ter uma facilidade de reusar esses espaços de memória. O perigo é perder o controle das 
    alteraçoes dos dados é grande se compartilhamos a referencia com varias variaveis.
    */


    int A = 2;
    int B = A; // B vale 2

    A++; // A vale 3
    B--; // B vale 1

    cout << A << endl;
    cout << B << endl;

    // ATRIBUIÇÃO POR REFERÊNCIA
    // referencia
    // https://learn.microsoft.com/pt-br/cpp/cpp/references-cpp?view=msvc-170&viewFallbackFrom=vs-2019

    int C = 10; //32 bits = 4 bytes
    cout << "O valor de C eh:  " << C << " \n e o endereco de C eh um valor hexadeciaml: "<< &C << endl;

    // se colocarmos outra variavel, notamos que as variaveis estao proximos na memoria 
    int D = 15; //32 bits = 4 bytes
    cout << "O valor de D eh:  " << D << " \n e o endereco de D eh um valor hexadeciaml: "<< &D << endl;

    // com o & temos a referencia na memoria, o endereço da da variavel onde se encontra o conteudo dela

    return 0;
}