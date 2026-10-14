Este é o plano da **rodada 1**: cada combinação roda **1 vez**, com os 102 cenários, e uma de cada vez.

| # | Modelo | Braço | Vezes | Cenários | Tempo estimado |
|---|---|---|---|---|---|
| 1 | Qwen2.5-Coder-14B | baseline | 1 | 102 | ~7,5 h |
| 2 | Qwen2.5-Coder-14B | destilação | 1 | 102 | ~7,5 h |
| 3 | CodeLlama-13B | baseline | 1 | 102 | ~6,5 h* |
| 4 | CodeLlama-13B | destilação | 1 | 102 | ~6,5 h* |
| 5 | Magicoder-S-CL-7B | baseline | 1 | 102 | ~3,5 h* |
| 6 | Magicoder-S-CL-7B | destilação | 1 | 102 | ~3,5 h* |
| | **Total** | | | **612 resultados** | **~35 h** |

\* São estimativas minhas: só o tempo do Qwen foi medido.

Se começar agora (quinta, ~23:50), deve terminar por volta de **sábado de manhã**.

**Fica para depois**, conforme a conversa com o professor:
- repetições extras, de 2 a 5, do Qwen e dos outros modelos;
- o WizardCoder-33B, na DGX.

Para começar, rode os **Comandos 20, 21 e 22** da mensagem anterior:
1. criar o `rodada1.sh`;
2. iniciar com `nohup`;
3. depois de ~2 minutos, conferir se apareceu o `Continue? [y/N] y` no log.

Me mande o resultado do Comando 22.