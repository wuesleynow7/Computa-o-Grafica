#include<stdio.h>
#include<stdlib.h>

/*
🧪 Exercício 6 — Criar e liberar dinamicamente uma estrutura

Tarefa:
Crie uma função struct Ponto* criaPonto(int x, int y) que:

- usa malloc para criar um novo ponto;

- armazena os valores;

- retorna o ponteiro.
*/


typedef struct ponto {
    int x, y;
} Ponto;

// primeiro fazemos...
// Criamos uma função que aloca memória dinamicamente para um Ponto
Ponto* criaPonto(int x, int y) {//aloca na heap e devolve um endereço.
    //O malloc pede memória na heap (memória dinâmica) para guardar o Ponto.

    // O malloc reserva espaço na heap.
    // Ele devolve o endereço desse espaço.
    // Esse endereço é armazenado em p.
    // E a função retorna esse endereço.
    Ponto* p = (Ponto*) malloc(sizeof(Ponto)); // malloc retorna o endereço de memória, ponto continua existindo mesmo depois que a função terminar, por isso use o malloc
    p->x = x; // acessamos o campo x com ->
    p->y = y; // acessamos o campo y com ->
    return p; // retornamos o  devolve o endereço da memória alocada
}

int main() {
    int x = 3, y = 6;


    //🧠 Analogia simples
    //Imagine a função criaPonto como uma fábrica que constrói um objeto (o Ponto) na memória principal (heap) e te entrega o endereço dele.
    //A variável p na main é só o papelzinho com o endereço de onde o objeto está guardado.
    //🔹 Quando a função termina → o “papelzinho” continua válido.
    //🔹 Quando você chama free(p) → o objeto é destruído.


    //🧩 3. E por que declarar Ponto* p na main?
    //➡️ Aqui:
    // criaPonto(3, 6) devolve o endereço do Ponto que está na heap;
    // p recebe esse endereço;
    // Agora você pode acessar os dados com p->x e p->y.

    // Porque você precisa de uma variável para guardar o endereço que a função retornou.
    // chamamos a função que cria o ponto dinamicamente
    Ponto* p = criaPonto(x, y);//Na verdade, você não cria de novo — você só guarda o endereço retornado pela função.

    //🧠 4. Por que isso é necessário?
    //Porque:
    //Se o Ponto fosse criado dentro da função sem malloc, ele estaria na stack (memória local);
    //Quando a função terminasse, ele seria destruído e o ponteiro apontaria para um espaço inválido;
    //O malloc garante que o dado permaneça existindo mesmo após o término da função.


    // 🔎 Exemplo visual
    //          Local                   Variável	                Valor	                Observação
    // Heap	                     |      (endereço 0x1000)  |    {x: 3, y: 6}	|   Onde o malloc criou o Ponto
    // Stack(main)	             |          p	           |    0x1000          |   Ponteiro que guarda o endereço do ponto
    // Stack(função criaPonto)   |          p 	           |    0x1000	        |   É destruído ao sair da função, mas o conteúdo na heap continua existindo


    // mostramos o endereço do ponteiro e seus valores
    printf("Endereco do ponto: %p\n", p);
    printf("Coordenadas: x = %d, y = %d\n", p->x, p->y);

    // depois fazemos...
    // liberamos a memória alocada
    free(p);

    return 0;
}