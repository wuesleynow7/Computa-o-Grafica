Vou revisar o que você já tem implementado contra a lista de 8 tarefas, apontando o que está pronto, o que está quebrado e o que falta.

## Status atual dos arquivos

**Tarefa 1 — Ler PPM P3 (`carregaArquivo`)**: ✅ já implementado, funciona no caso básico. Mas tem dois problemas:
- Não verifica se `fopen` retornou `NULL` antes de usar `arquivo` — se o arquivo não existir, vai crashar com segfault.
- Não confere se a linha1 realmente é `"P3"`. Se alguém passar um P6 sem querer, vai tentar ler como texto e vai dar lixo. Vale um `strncmp(linha1, "P3", 2)` com aviso de erro.

**Tarefa 2 — Gravar PPM P3 (`salvaImagem`)**: ✅ já implementado, parece correto — formato e cabeçalho batem com o padrão P3.

**Tarefa 3 — `putPixel`**: ⚠️ implementado, mas falta a verificação de limites que o enunciado pede explicitamente. Hoje se você chamar `putPixel(fig, 999, 999, ...)` numa imagem 640x480, vai escrever fora do array alocado (undefined behavior / corrupção de memória). Você precisa adicionar um `if` no início checando `coordenada_x >= 0 && coordenada_x < largura && coordenada_y >= 0 && coordenada_y < altura` antes de escrever — e decidir o que fazer quando estiver fora (ignorar silenciosamente é o mais comum).

Repare também que sua convenção de eixos está meio misturada: em `carimbaImagem` você usa `coordenada_x_figura_1` indexando a primeira dimensão da matriz (que na prática é a **linha/altura**), enquanto no `main.c` os comentários chamam de "coluna" e "linha". Vale decidir uma convenção fixa (eu sugeriria `[linha][coluna]` = `[y][x]`) e ser consistente em todas as funções, senão você vai se perder depois.

**Tarefa 4 — `get_red`/`get_green`/`get_blue` e `getPixel`**: ❌ não feito. `getPixel` está declarado no `.c` mas o corpo está vazio (nem tem `return`, o que é UB numa função que promete retornar `pixel*`), e nem está no `.h`. Você precisa:
- Três funções simples `int get_red(image* fig, int x, int y)` etc., cada uma só retornando o valor da matriz correspondente (com a mesma checagem de limites da tarefa 3 — o que fazer se pedirem coordenada inválida? retornar -1 ou 0 é uma convenção comum).
- Uma função que monte um `pixel` (struct que você já tem em `ppmstruct.h`) com os três valores e retorne por valor (ou por ponteiro alocado, mas por valor é mais simples e evita você ter que dar `free` depois).

**Tarefa 5 — `carimba` com transparência**: ❌ o `carimbaImagem` atual não faz nada de útil — a linha `figura_1->green[coordenada_x_figura_1][coordenada_y_figura_1];` só lê um valor e descarta, não copia nada. E a condição de checagem de tamanho tem um bug de precedência de operadores: `a && b < c && d` não faz o que parece — o `&&` tem prioridade menor que `<`, mas mesmo assim `carimbo->largura` sozinho não é uma comparação, é só "carimbo->largura != 0", o que não verifica nada relacionado ao tamanho da figura_1.

O que essa função precisa de fato:
- Dois loops aninhados percorrendo **as dimensões do carimbo** (não da figura_1) — para cada pixel `(i,j)` do carimbo, calcular a posição destino `(x+i, y+j)` na `figura_1`.
- Para cada posição destino, checar se está dentro dos limites de `figura_1` (reaproveite a lógica de bounds checking da tarefa 3 — dá pra chamar seu próprio `putPixel` aqui, que já vai ter a checagem).
- Se a opção de transparência estiver ativada, comparar o pixel do carimbo com a cor-chave (ex: `r,g,b` passados como parâmetro ou uma constante) e, se bater, pular esse pixel (não escrever).
- Pense na assinatura como algo do tipo `void carimba(image* dest, image* carimbo, int x, int y, int usa_transparencia, int tr, int tg, int tb)`.

**Tarefa 6 — Suporte a P6 (binário)**: ❌ não iniciado. A diferença principal:
- No cabeçalho, o magic number é `"P6"` em vez de `"P3"`.
- Depois do `maxval`, em vez de números ASCII separados por espaço, os valores RGB vêm como **bytes binários crus**, um após o outro (`fread` em vez de `fscanf`), e é importante ler exatamente **um único caractere de whitespace** depois do maxval antes de começar a ler os bytes binários (isso costuma ser a maior pegadinha).
- Uma abordagem comum: fazer as funções de leitura/escrita detectarem o subtipo pela string do cabeçalho e chamarem uma sub-rotina interna (`carregaP3`/`carregaP6`) mantendo a mesma interface pública `carregaArquivo`.

**Tarefa 7 — Maze com carimbo de sprites**: ❌ não iniciado. Passos:
1. Ler `maze.txt` linha por linha (`fgets`) numa matriz de `char` (ou até um vetor de strings), guardando altura/largura do labirinto em número de símbolos.
2. Carregar `arbusto.ppm` e `chao.ppm` uma vez só (fora do loop) com seu `carregaArquivo`.
3. Criar uma imagem final com dimensões `largura_labirinto * largura_do_tile` × `altura_labirinto * altura_do_tile`.
4. Percorrer a matriz de char; para cada símbolo, calcular a coordenada em pixels (`i * altura_tile`, `j * largura_tile`) e chamar seu `carimba` (tarefa 5) ali.
5. Salvar com `salvaImagem`.

**Tarefa 8 — Tiling genérico com dicionário símbolo→imagem**: ❌ não iniciado, mas é essencialmente a tarefa 7 generalizada. A parte nova é ler um arquivo de "dicionário" (`#,arbusto.ppm` etc.) e montar uma estrutura de associação símbolo↔imagem antes de processar o mapa — pode ser um array de structs `{ char simbolo; image* img; }` percorrido linearmente (não precisa de hash map pra um punhado de tiles).

## Sobre o `main.c`

Os comentários que sobraram lá já estão desatualizados em relação ao seu progresso real:
- `salvaImagem`/`carregaArquivo` → já existem, o comentário pode sair.
- "Corrija a apaga" → já parece corrigida (o loop libera as três matrizes linha a linha e depois os três ponteiros de topo e o struct — está certo).
- Falta mesmo: preencher imagem com cores aleatórias + salvar, gerar padrão arco-íris + salvar, e testar `putPixel`/`getPixel` de fato (hoje o `main` só chama `inicializa` e `mostra`).
- Vale também corrigir o bug no `mostra()`: falta um espaço entre os trios RGB no `printf` (`"%d %d %d"` sem separador entre pixels vai grudar os números, ex: `2552550 0 0`).

Quer que eu vá te guiando tarefa por tarefa (começando pela 3 e 4, que são as mais curtas) enquanto você escreve o código?