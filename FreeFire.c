// arquivo: inventario.c
// Mochila de Loot — Nível Inicial


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// =============================
// Struct que representa um item
// =============================
typedef struct {
    char nome[30];     // ex: "Pistola 9mm"
    char tipo[20];     // ex: "arma", "munição", "cura", "ferramenta"
    int quantidade;    // ex: 30
} Item;

// =============================
// Protótipos das funções
// =============================
void limparEntrada(void);
void lerLinha(char *dest, size_t tam);
int inserirItem(Item mochila[], int *qtd);
int buscarItem(Item mochila[], int qtd, const char *nome);
int removerItem(Item mochila[], int *qtd, const char *nome);
void listarItens(const Item mochila[], int qtd);

// =============================
// Funções utilitárias de I/O
// =============================
void limparEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* joga fora */ }
}

void lerLinha(char *dest, size_t tam) {
    if (fgets(dest, (int)tam, stdin) != NULL) {
        size_t len = strlen(dest);
        if (len > 0 && dest[len - 1] == '\n') dest[len - 1] = '\0';
    } else {
        // caso raro: garante string válida
        if (tam > 0) dest[0] = '\0';
        clearerr(stdin);
    }
}

// =============================
// CRUD básico da mochila
// =============================
int inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\n⚠️  Mochila cheia! (capacidade: %d)\n", MAX_ITENS);
        return 0;
    }

    Item novo;
    printf("\n> Nome do item: ");
    lerLinha(novo.nome, sizeof(novo.nome));

    if (strlen(novo.nome) == 0) {
        printf("Nome vazio não rola. Tenta de novo.\n");
        return 0;
    }

    printf("> Tipo (arma/munição/cura/ferramenta): ");
    lerLinha(novo.tipo, sizeof(novo.tipo));
    if (strlen(novo.tipo) == 0) {
        printf("Tipo vazio não rola. Tenta de novo.\n");
        return 0;
    }

    printf("> Quantidade: ");
    if (scanf("%d", &novo.quantidade) != 1) {
        printf("Quantidade inválida.\n");
        limparEntrada();
        return 0;
    }
    limparEntrada();

    if (novo.quantidade < 0) {
        printf("Quantidade negativa? Aí não. :)\n");
        return 0;
    }

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("\n✅ Item cadastrado com sucesso!\n");
    return 1;
}

int buscarItem(Item mochila[], int qtd, const char *nome) {
    // Busca sequencial: simples e eficiente o bastante para até 10 itens
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

int removerItem(Item mochila[], int *qtd, const char *nome) {
    int pos = buscarItem(mochila, *qtd, nome);
    if (pos == -1) return 0;

    // Desloca os elementos para fechar o "buraco"
    for (int i = pos; i < *qtd - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    (*qtd)--;
    return 1;
}

void listarItens(const Item mochila[], int qtd) {
    printf("\n================ Inventário Atual ================\n");
    if (qtd == 0) {
        printf("(vazio) — sem loot por enquanto, bora vasculhar!\n");
        printf("==================================================\n");
        return;
    }

    printf("%-3s | %-30s | %-12s | %-10s\n", "#", "Nome", "Tipo", "Quantidade");
    printf("----+--------------------------------+--------------+------------\n");
    for (int i = 0; i < qtd; i++) {
        printf("%-3d | %-30s | %-12s | %-10d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("==================================================\n");
}

// =============================
// Programa principal 
// =============================
int main(void) {
    Item mochila[MAX_ITENS];
    int qtd = 0;

    int opcao = -1;
    char buffer[64];

    printf("===== Mochila de Loot (Nível Inicial) =====\n");
    printf("Organize seus itens e tome boas decisões rápidas. ;)\n");

    do {
        printf("\n--- Menu ---\n");
        printf("1) Cadastrar item\n");
        printf("2) Remover item\n");
        printf("3) Buscar item\n");
        printf("4) Listar itens\n");
        printf("0) Sair\n");
        printf("> Escolha: ");

        lerLinha(buffer, sizeof(buffer));
        if (sscanf(buffer, "%d", &opcao) != 1) {
            printf("Opção inválida.\n");
            continue;
        }

        switch (opcao) {
            case 1: {
                if (inserirItem(mochila, &qtd)) {
                    listarItens(mochila, qtd); // mostra como ficou
                } else {
                    // mesmo em erro, mantém o feedback visual do estado atual
                    listarItens(mochila, qtd);
                }
            } break;

            case 2: {
                if (qtd == 0) {
                    printf("\nNada para remover, a mochila está vazia.\n");
                    break;
                }
                char nome[30];
                printf("\n> Nome do item para remover: ");
                lerLinha(nome, sizeof(nome));

                if (removerItem(mochila, &qtd, nome)) {
                    printf("🗑️  Removido: %s\n", nome);
                } else {
                    printf("Não achei \"%s\" na mochila.\n", nome);
                }
                listarItens(mochila, qtd);
            } break;

            case 3: {
                if (qtd == 0) {
                    printf("\nBusca vazia: a mochila está sem itens.\n");
                    break;
                }
                char nome[30];
                printf("\n> Nome do item para buscar: ");
                lerLinha(nome, sizeof(nome));

                int pos = buscarItem(mochila, qtd, nome);
                if (pos >= 0) {
                    printf("\n🔎 Encontrei!\n");
                    printf("Nome: %s\n", mochila[pos].nome);
                    printf("Tipo: %s\n", mochila[pos].tipo);
                    printf("Qtd : %d\n", mochila[pos].quantidade);
                } else {
                    printf("\nNada feito: \"%s\" não está na mochila.\n", nome);
                }
                listarItens(mochila, qtd);
            } break;

            case 4:
                listarItens(mochila, qtd);
                break;

            case 0:
                printf("\nSaindo... boa sorte no loot! 🍀\n");
                break;

            default:
                printf("Opção inexistente. Tenta outra.\n");
        }
    } while (opcao != 0);

    return 0;
}
