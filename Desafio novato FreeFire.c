#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Struct Item:
// Representa um item da mochila do jogador
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Item;

// Enum para critérios de ordenação
typedef enum {
    NOME = 1,
    TIPO,
    PRIORIDADE
} CriterioOrdenacao;

// Vetor mochila
Item mochila[MAX_ITENS];

// Variáveis globais
int numItens = 0;
int comparacoes = 0;
bool ordenadaPorNome = false;

// Protótipos das funções
void limparTela();
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void menuDeOrdenacao();
void insertionSort(CriterioOrdenacao criterio);

int main() {

    int opcao;

    do {
        exibirMenu();

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

            case 1:
                inserirItem();
                listarItens();
                break;

            case 2:
                removerItem();
                listarItens();
                break;

            case 3:
                listarItens();
                break;

            case 4:
                menuDeOrdenacao();
                listarItens();
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// Simula limpeza da tela
void limparTela() {
    for (int i = 0; i < 30; i++) {
        printf("\n");
    }
}

// Exibe menu principal
void exibirMenu() {

    printf("\n========== MOCHILA FREE FIRE ==========\n");
    printf("Itens armazenados: %d/%d\n",
           numItens, MAX_ITENS);

    printf("\n1 - Adicionar item");
    printf("\n2 - Remover item");
    printf("\n3 - Listar itens");
    printf("\n4 - Ordenar itens");
    printf("\n0 - Sair");

    printf("\n=======================================\n");
}

// Inserir item
void inserirItem() {

    if (numItens >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("\nNome do item: ");
    fgets(mochila[numItens].nome, 30, stdin);
    mochila[numItens].nome[
        strcspn(mochila[numItens].nome, "\n")
    ] = '\0';

    printf("Tipo do item: ");
    fgets(mochila[numItens].tipo, 20, stdin);
    mochila[numItens].tipo[
        strcspn(mochila[numItens].tipo, "\n")
    ] = '\0';

    printf("Quantidade: ");
    scanf("%d",
          &mochila[numItens].quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d",
          &mochila[numItens].prioridade);

    getchar();

    numItens++;
    ordenadaPorNome = false;

    printf("\nItem adicionado com sucesso!\n");
}

// Remover item
void removerItem() {

    if (numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nomeBusca[30];
    bool encontrado = false;

    printf("\nDigite o nome do item para remover: ");
    fgets(nomeBusca, 30, stdin);

    nomeBusca[
        strcspn(nomeBusca, "\n")
    ] = '\0';

    for (int i = 0; i < numItens; i++) {

        if (strcmp(mochila[i].nome,
                   nomeBusca) == 0) {

            encontrado = true;

            // Reorganiza o vetor
            for (int j = i;
                 j < numItens - 1;
                 j++) {

                mochila[j] =
                    mochila[j + 1];
            }

            numItens--;

            printf("\nItem removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem não encontrado!\n");
    }
}

// Listar itens
void listarItens() {

    if (numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n========= ITENS DA MOCHILA =========\n");

    printf("%-20s %-15s %-10s %-10s\n",
           "Nome",
           "Tipo",
           "Qtd",
           "Prioridade");

    for (int i = 0;
         i < numItens;
         i++) {

        printf("%-20s %-15s %-10d %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

// Menu de ordenação
void menuDeOrdenacao() {

    int opcao;

    printf("\nOrdenar por:\n");
    printf("1 - Nome\n");
    printf("2 - Tipo\n");
    printf("3 - Prioridade\n");

    printf("Escolha: ");
    scanf("%d", &opcao);
    getchar();

    comparacoes = 0;

    switch (opcao) {

        case 1:
            insertionSort(NOME);
            printf("\nItens ordenados por nome!\n");
            break;

        case 2:
            insertionSort(TIPO);
            printf("\nItens ordenados por tipo!\n");
            break;

        case 3:
            insertionSort(PRIORIDADE);
            printf("\nItens ordenados por prioridade!\n");
            break;

        default:
            printf("\nOpção inválida!\n");
            return;
    }

    printf("Comparações realizadas: %d\n",
           comparacoes);
}

// Insertion Sort
void insertionSort(
    CriterioOrdenacao criterio) {

    for (int i = 1;
         i < numItens;
         i++) {

        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {

            comparacoes++;

            int comparar = 0;

            switch (criterio) {

                case NOME:
                    comparar =
                        strcmp(
                            mochila[j].nome,
                            chave.nome
                        );
                    break;

                case TIPO:
                    comparar =
                        strcmp(
                            mochila[j].tipo,
                            chave.tipo
                        );
                    break;

                case PRIORIDADE:
                    comparar =
                        mochila[j]
                            .prioridade <
                        chave.prioridade;
                    break;
            }

            if (comparar > 0 ||
                (criterio ==
                     PRIORIDADE &&
                 comparar)) {

                mochila[j + 1] =
                    mochila[j];

                j--;

            } else {
                break;
            }
        }

        mochila[j + 1] = chave;
    }
}