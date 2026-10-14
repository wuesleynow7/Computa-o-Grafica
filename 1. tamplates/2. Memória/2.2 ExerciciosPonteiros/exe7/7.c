#include<stdio.h>
#include<stdlib.h>
/*
🧪 Exercício 7 — Misturando tudo

Tarefa:
Implemente um mini “banco de dados” de alunos:

typedef struct {
    char nome[50];
    int idade;
} Aluno;


Crie uma função que:

- aloca dinamicamente espaço para n alunos;

- pede para o usuário digitar os nomes e idades;

- retorna o ponteiro para o vetor.

Depois, outra função que:

- recebe o ponteiro e imprime todos os alunos;

- e outra que libera a memória.

💡 Dica:
Aqui você junta:

- ponteiro para estrutura,

- ponteiro para vetor,

- e passagem por referência.

############################################ pseudo codigo

função criaAlunos(n):
    aloca vetor de tamanho n
    para cada aluno i:
        leia nome e idade
    retorna vetor

função imprimeAlunos(vetor, n):
    para cada aluno i:
        imprime nome e idade

função liberaAlunos(vetor):
    free(vetor)

main:
    lê n
    alunos = criaAlunos(n)
    imprimeAlunos(alunos, n)
    liberaAlunos(alunos)
*/

typedef struct {
    char nome[50];
    int idade;
} Aluno;


Aluno* cadastrarAlunoNoBanco(int n){

    // 1️⃣ Aloca dinamicamente memória para n alunos, Cria espaço na heap para guardar n structs do tipo Aluno.
    Aluno* listaDeAlunos = (Aluno*) malloc(n * sizeof(Aluno));

    // 2️⃣ Verifica se a alocação deu certo
    if (listaDeAlunos == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1); // encerra o programa se falhar
    }

    // 3️⃣ Preenche os dados dos alunos
    for (int i = 0; i < n; i++) {
        printf("Digite o nome do aluno %d: ", i + 1);
        scanf("%s", listaDeAlunos[i].nome);

        printf("Digite a idade do aluno %d: ", i + 1);
        scanf("%d", &listaDeAlunos[i].idade);
    }

    // 4️⃣ Retorna o endereço do primeiro aluno do vetor, que está na heap.
    return listaDeAlunos;

}


int main(){


        
}