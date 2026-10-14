# Compilação em C e Makefile

## Sumário

1. [Compilando com GCC](#1-compilando-com-gcc)
   - [1.1 Compilação simples](#11-compilação-simples)
   - [1.2 Flags mais usadas](#12-flags-mais-usadas)
   - [1.3 Projetos com mais de um arquivo](#13-projetos-com-mais-de-um-arquivo)
2. [Erro comum: função indefinida (ex: `sin`)](#2-erro-comum-função-indefinida-ex-sin)
   - [2.1 Causa](#21-causa)
   - [2.2 Solução: flag `-lm`](#22-solução-flag--lm)
3. [O que é Makefile](#3-o-que-é-makefile)
   - [3.1 O problema que o `make` resolve](#31-o-problema-que-o-make-resolve)
   - [3.2 O que é o `make`](#32-o-que-é-o-make)
   - [3.3 O que são arquivos `.o`](#33-o-que-são-arquivos-o)
   - [3.4 Analogia](#34-analogia)
4. [Estrutura de um Makefile](#4-estrutura-de-um-makefile)
   - [4.1 Sintaxe básica](#41-sintaxe-básica)
   - [4.2 Exemplo simples (um arquivo)](#42-exemplo-simples-um-arquivo)
5. [Makefile explicado linha por linha](#5-makefile-explicado-linha-por-linha)
   - [5.1 Variáveis](#51-variáveis)
   - [5.2 Regras](#52-regras)
   - [5.3 Regra principal (linkagem)](#53-regra-principal-linkagem)
   - [5.4 Regras de cada `.o` (compilação)](#54-regras-de-cada-o-compilação)
   - [5.5 `clean`](#55-clean)
   - [5.6 A "mágica" central](#56-a-mágica-central)
6. [Makefiles prontos para o projeto de PPM](#6-makefiles-prontos-para-o-projeto-de-ppm)
   - [6.1 Opção explícita](#61-opção-explícita)
   - [6.2 Opção automática (wildcard)](#62-opção-automática-wildcard)
7. [Como usar](#7-como-usar)

---

## 1. Compilando com GCC

### 1.1 Compilação simples

```bash
gcc programa.c -o programa
```

Gera um executável chamado `programa`, executado com:

```bash
./programa
```

### 1.2 Flags mais usadas

```bash
gcc -Wall -Wextra -g programa.c -o programa
```

| Flag | O que faz |
|---|---|
| `-Wall` | Ativa avisos comuns |
| `-Wextra` | Ativa avisos extras |
| `-g` | Inclui informações de debug (útil com `gdb`) |
| `-o programa` | Define o nome do executável (padrão seria `a.out`) |

### 1.3 Projetos com mais de um arquivo

Tudo de uma vez:

```bash
gcc arquivo1.c arquivo2.c -o programa
```

Ou em etapas (gerando `.o` primeiro):

```bash
gcc -c arquivo1.c -o arquivo1.o
gcc -c arquivo2.c -o arquivo2.o
gcc arquivo1.o arquivo2.o -o programa
```

---

## 2. Erro comum: função indefinida (ex: `sin`)

Erro típico ao usar funções de `math.h`:

```
/usr/bin/ld: referência não definida para "sin"
collect2: error: ld returned 1 exit status
```

### 2.1 Causa

No Linux, funções matemáticas (`sin`, `cos`, `sqrt`, `pow`, etc.) ficam em uma biblioteca separada, a `libm`. Incluir `#include <math.h>` não basta — é preciso linkar a biblioteca também.

### 2.2 Solução: flag `-lm`

```bash
gcc -Wall -Wextra -g test.c -o out -lm
```

**Importante**: `-lm` deve vir **depois** do nome do arquivo `.c` (ou de tudo que depende dela) — é uma particularidade da ordem de resolução de símbolos do `ld`. Se colocada antes, o erro pode persistir.

Se a compilação falha por erro de linkagem, o executável **não é criado** — por isso `./out` retorna "arquivo inexistente" até o erro ser corrigido.

---

## 3. O que é Makefile

Um **Makefile** é um arquivo de configuração usado pela ferramenta `make` para automatizar a compilação de projetos em C (e outras linguagens). Em vez de digitar comandos `gcc` toda vez, você define regras uma vez e roda apenas `make`.

### 3.1 O problema que o `make` resolve

Compilar um projeto com vários arquivos manualmente:

```bash
gcc main.c ppm.c carimba.c -o programa -lm
```

Dois problemas:

1. É chato digitar o comando toda vez que se testa uma mudança.
2. É lento em projetos grandes: o GCC recompila **todos** os arquivos mesmo que só um tenha mudado.

### 3.2 O que é o `make`

`make` é um programa (já vem instalado no Linux) que lê o `Makefile` e executa comandos automaticamente, olhando a data de modificação dos arquivos — só recompila o que realmente mudou.

O Makefile funciona como uma **receita**:
- "para gerar `programa`, preciso de `main.o`, `ppm.o` e `carimba.o`"
- "para gerar `ppm.o`, preciso compilar `ppm.c`"
- etc.

### 3.3 O que são arquivos `.o`

Ao compilar um `.c`, o GCC passa por duas etapas:

1. **Compilação**: transforma `.c` em código de máquina "incompleto" → gera um arquivo `.o` (**arquivo objeto**)
2. **Linkagem**: junta todos os `.o` em um executável final

O comando `gcc main.c ppm.c carimba.c -o programa` faz as duas etapas de uma vez, sem deixar os `.o` visíveis. O Makefile separa isso para poder pular a compilação de arquivos que não mudaram.

### 3.4 Analogia

Pense em montar um sanduíche com ingredientes preparados separadamente (pão, carne, molho). Se o molho já foi preparado ontem e continua bom, não faz sentido prepará-lo de novo — só se prepara o que faltou. É isso que o `make` faz com os `.o`.

---

## 4. Estrutura de um Makefile

### 4.1 Sintaxe básica

```makefile
alvo: dependências
	comando
```

**Atenção**: a indentação do comando precisa ser **TAB**, não espaços — erro comum que quebra o Makefile.

### 4.2 Exemplo simples (um arquivo)

```makefile
programa: test.c
	gcc -Wall -Wextra -g test.c -o programa -lm
```

Uso:

```bash
make
```

---

## 5. Makefile explicado linha por linha

Base de referência:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm

programa: main.o ppm.o carimba.o
	$(CC) main.o ppm.o carimba.o -o programa $(LDFLAGS)

main.o: main.c ppm.h carimba.h
	$(CC) $(CFLAGS) -c main.c

ppm.o: ppm.c ppm.h
	$(CC) $(CFLAGS) -c ppm.c

carimba.o: carimba.c carimba.h ppm.h
	$(CC) $(CFLAGS) -c carimba.c

clean:
	rm -f *.o programa
```

### 5.1 Variáveis

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm
```

- `CC` (Compiler): nome do compilador
- `CFLAGS` (Compiler Flags): flags de compilação
- `LDFLAGS` (Linker Flags): flags de linkagem

São nomes convencionais (o `make` já os reconhece por padrão), mas poderiam ter qualquer nome. Uso: `$(CC)`, `$(CFLAGS)`.

### 5.2 Regras

```makefile
alvo: dependências
	comando
```

- **alvo**: o que a regra produz (um arquivo)
- **dependências**: de quais arquivos o alvo precisa
- **comando**: o que rodar para gerar o alvo (TAB, não espaço)

### 5.3 Regra principal (linkagem)

```makefile
programa: main.o ppm.o carimba.o
	$(CC) main.o ppm.o carimba.o -o programa $(LDFLAGS)
```

Diz: "para gerar `programa`, `main.o`, `ppm.o` e `carimba.o` precisam existir e estar atualizados".

Ao rodar `make` (sem argumento), ele olha o **primeiro alvo do arquivo** (aqui, `programa`). Antes de rodar o comando, verifica se as dependências existem e estão em dia; se não, vai atrás das regras que as geram.

O comando é a etapa de **linkagem**: junta os três `.o` num executável.

### 5.4 Regras de cada `.o` (compilação)

```makefile
ppm.o: ppm.c ppm.h
	$(CC) $(CFLAGS) -c ppm.c
```

"`ppm.o` depende de `ppm.c` e `ppm.h`". Se algum dos dois mudar, o comando roda de novo.

`-c` = "só compila, não linka" (gera o `.o`).

`carimba.o` inclui `ppm.h` como dependência porque `carimba.c` provavelmente faz `#include "ppm.h"`. Regra geral: se um `.c` inclui um `.h`, esse `.h` entra na lista de dependências — senão o `make` não percebe quando o header muda.

### 5.5 `clean`

```makefile
clean:
	rm -f *.o programa
```

Sem dependências — existe só para rodar manualmente com `make clean`, apagando `.o` e o executável. Útil para forçar recompilação total.

### 5.6 A "mágica" central

O `make` compara a **data de modificação** dos arquivos. Se `ppm.o` for mais novo que `ppm.c`, entende que nada mudou e **pula** o comando. Só recompila o que precisa.

---

## 6. Makefiles prontos para o projeto de PPM

### 6.1 Opção explícita

Mais didática — cada `.o` listado manualmente:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm

# Executável final
programa: main.o ppm.o carimba.o
	$(CC) main.o ppm.o carimba.o -o programa $(LDFLAGS)

# Regras individuais: cada .o depende do .c e dos headers usados nele
main.o: main.c ppm.h carimba.h
	$(CC) $(CFLAGS) -c main.c

ppm.o: ppm.c ppm.h
	$(CC) $(CFLAGS) -c ppm.c

carimba.o: carimba.c carimba.h ppm.h
	$(CC) $(CFLAGS) -c carimba.c

clean:
	rm -f *.o programa
```

> Ajuste os `.h` de cada regra conforme o que cada `.c` de fato inclui via `#include`.

### 6.2 Opção automática (wildcard)

Menos verbosa, escala melhor com mais arquivos:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

programa: $(OBJS)
	$(CC) $(OBJS) -o programa $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o programa
```

- `$(wildcard *.c)`: pega automaticamente todos os `.c` da pasta
- `%.o: %.c`: regra genérica que compila qualquer `.c` sem listar um por um
- `$<`: primeiro pré-requisito (o `.c`)
- `$@`: o alvo (o `.o`)

**Trade-off**: não rastreia dependência de headers automaticamente — se só um `.h` mudar, pode não recompilar quem o inclui. Para projeto pequeno, geralmente não é problema.

---

## 7. Como usar

Salve como `Makefile` (sem extensão, M maiúsculo por convenção) na pasta do projeto:

```bash
make        # compila
make clean  # limpa .o e o executável
```
