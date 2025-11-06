<!-- arquivo: README.md -->

# Mochila de Loot — Nível Novato

Sistema simples de inventário para o começo da partida: cadastra, remove, lista e busca itens usando `struct` e vetor sequencial. Direto ao ponto e pensado pra decidir rápido no loot.

- `struct Item` com `nome`, `tipo` e `quantidade`
- Vetor de até **10** itens (capacidade fixa)
- Funções: `inserirItem()`, `removerItem()`, `listarItens()`, `buscarItem()`
- Busca sequencial por nome
- Saída sempre amigável (eu gosto de ver o estado depois de cada ação)

## Como eu organizo

- Arquivo principal: `inventario.c`
- Menu textual simples com `scanf`/`fgets` bem comportados
- Remoção com deslocamento pra manter a lista compacta

## Compilar & rodar

```bash
gcc inventario.c -o inventario
./inventario
