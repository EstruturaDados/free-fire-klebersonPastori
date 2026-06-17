#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 100

//=====================================================
// STRUCTS
//=====================================================

// Estrutura do item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura do nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

//=====================================================
// VARIÁVEIS GLOBAIS
//=====================================================

// Mochila com vetor
Item mochilaVetor[MAX_ITENS];
int quantidadeItensVetor = 0;

// Mochila com lista encadeada
No* mochilaLista = NULL;

// Contadores de comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

//=====================================================
// FUNÇÕES AUXILIARES
//=====================================================

// Limpa buffer do teclado
void limparBuffer() {
    while (getchar() != '\n');
}

//=====================================================
// FUNÇÕES DO VETOR
//=====================================================

// Inserir item no vetor
void inserirItemVetor() {

    if (quantidadeItensVetor >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    Item novoItem;

    printf("\nNome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    printf("Tipo do item: ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();

    mochilaVetor[quantidadeItensVetor] = novoItem;
    quantidadeItensVetor++;

    printf("\nItem inserido com sucesso!\n");
}

// Remover item do vetor pelo nome
void removerItemVetor() {

    if (quantidadeItensVetor == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nomeBusca[30];
    int encontrado = 0;

    printf("\nDigite o nome do item para remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < quantidadeItensVetor; i++) {

        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {

            for (int j = i; j < quantidadeItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }

            quantidadeItensVetor--;
            encontrado = 1;

            printf("\nItem removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem nao encontrado!\n");
    }
}

// Listar itens do vetor
void listarItensVetor() {

    if (quantidadeItensVetor == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n===== MOCHILA (VETOR) =====\n");

    for (int i = 0; i < quantidadeItensVetor; i++) {

        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", mochilaVetor[i].nome);
        printf("Tipo: %s\n", mochilaVetor[i].tipo);
        printf("Quantidade: %d\n",
               mochilaVetor[i].quantidade);
    }
}

// Busca sequencial no vetor
void buscarSequencialVetor() {

    char nomeBusca[30];
    comparacoesSequencial = 0;

    printf("\nDigite o nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < quantidadeItensVetor; i++) {

        comparacoesSequencial++;

        if (strcmp(mochilaVetor[i].nome,
                   nomeBusca) == 0) {

            printf("\nItem encontrado!\n");
            printf("Nome: %s\n",
                   mochilaVetor[i].nome);
            printf("Tipo: %s\n",
                   mochilaVetor[i].tipo);
            printf("Quantidade: %d\n",
                   mochilaVetor[i].quantidade);

            printf("Comparacoes: %d\n",
                   comparacoesSequencial);
            return;
        }
    }

    printf("\nItem nao encontrado!\n");
    printf("Comparacoes: %d\n",
           comparacoesSequencial);
}

// Ordenar vetor por nome usando Bubble Sort
void ordenarVetor() {

    Item temporario;

    for (int i = 0;
         i < quantidadeItensVetor - 1;
         i++) {

        for (int j = 0;
             j < quantidadeItensVetor - i - 1;
             j++) {

            if (strcmp(
                    mochilaVetor[j].nome,
                    mochilaVetor[j + 1].nome
                ) > 0) {

                temporario =
                    mochilaVetor[j];

                mochilaVetor[j] =
                    mochilaVetor[j + 1];

                mochilaVetor[j + 1] =
                    temporario;
            }
        }
    }

    printf("\nItens ordenados por nome!\n");
}

// Busca binária no vetor
void buscarBinariaVetor() {

    char nomeBusca[30];

    printf("\nDigite o nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int inicio = 0;
    int fim = quantidadeItensVetor - 1;

    comparacoesBinaria = 0;

    while (inicio <= fim) {

        comparacoesBinaria++;

        int meio =
            (inicio + fim) / 2;

        int resultado =
            strcmp(
                mochilaVetor[meio].nome,
                nomeBusca
            );

        if (resultado == 0) {

            printf("\nItem encontrado!\n");
            printf("Nome: %s\n",
                   mochilaVetor[meio].nome);
            printf("Tipo: %s\n",
                   mochilaVetor[meio].tipo);
            printf("Quantidade: %d\n",
                   mochilaVetor[meio]
                   .quantidade);

            printf("Comparacoes: %d\n",
                   comparacoesBinaria);
            return;
        }

        if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\nItem nao encontrado!\n");
    printf("Comparacoes: %d\n",
           comparacoesBinaria);
}

//=====================================================
// FUNÇÕES DA LISTA ENCADEADA
//=====================================================

// Inserir item na lista
void inserirItemLista() {

    No* novoNo =
        (No*) malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("\nErro de memoria!\n");
        return;
    }

    printf("\nNome do item: ");
    fgets(novoNo->dados.nome,
          30,
          stdin);

    novoNo->dados.nome[
        strcspn(
            novoNo->dados.nome,
            "\n")
    ] = '\0';

    printf("Tipo do item: ");
    fgets(novoNo->dados.tipo,
          20,
          stdin);

    novoNo->dados.tipo[
        strcspn(
            novoNo->dados.tipo,
            "\n")
    ] = '\0';

    printf("Quantidade: ");
    scanf("%d",
          &novoNo->dados.quantidade);

    limparBuffer();

    novoNo->proximo =
        mochilaLista;

    mochilaLista =
        novoNo;

    printf("\nItem inserido com sucesso!\n");
}

// Remover item da lista
void removerItemLista() {

    char nomeBusca[30];

    printf("\nDigite o nome do item: ");
    fgets(nomeBusca, 30, stdin);

    nomeBusca[
        strcspn(nomeBusca, "\n")
    ] = '\0';

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL) {

        if (strcmp(
                atual->dados.nome,
                nomeBusca
            ) == 0) {

            if (anterior == NULL) {
                mochilaLista =
                    atual->proximo;
            } else {
                anterior->proximo =
                    atual->proximo;
            }

            free(atual);

            printf(
                "\nItem removido!\n"
            );

            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf(
        "\nItem nao encontrado!\n"
    );
}

// Listar itens da lista
void listarItensLista() {

    if (mochilaLista == NULL) {

        printf(
            "\nLista vazia!\n"
        );

        return;
    }

    No* atual =
        mochilaLista;

    printf(
        "\n===== MOCHILA (LISTA) =====\n"
    );

    while (atual != NULL) {

        printf("\nNome: %s\n",
               atual->dados.nome);

        printf("Tipo: %s\n",
               atual->dados.tipo);

        printf("Quantidade: %d\n",
               atual->dados.quantidade);

        atual =
            atual->proximo;
    }
}

// Busca sequencial na lista
void buscarSequencialLista() {

    char nomeBusca[30];

    comparacoesSequencial = 0;

    printf("\nDigite o nome do item: ");
    fgets(nomeBusca, 30, stdin);

    nomeBusca[
        strcspn(nomeBusca, "\n")
    ] = '\0';

    No* atual =
        mochilaLista;

    while (atual != NULL) {

        comparacoesSequencial++;

        if (strcmp(
                atual->dados.nome,
                nomeBusca
            ) == 0) {

            printf(
                "\nItem encontrado!\n"
            );

            printf("Nome: %s\n",
                   atual->dados.nome);

            printf("Tipo: %s\n",
                   atual->dados.tipo);

            printf("Quantidade: %d\n",
                   atual->dados.quantidade);

            printf("Comparacoes: %d\n",
                   comparacoesSequencial);

            return;
        }

        atual =
            atual->proximo;
    }

    printf(
        "\nItem nao encontrado!\n"
    );

    printf(
        "Comparacoes: %d\n",
        comparacoesSequencial
    );
}

//=====================================================
// MENUS
//=====================================================

void menuVetor() {

    int opcao;

    do {

        printf("\n===== MOCHILA VETOR =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Busca sequencial\n");
        printf("5 - Ordenar vetor\n");
        printf("6 - Busca binaria\n");
        printf("0 - Voltar\n");

        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {

            case 1:
                inserirItemVetor();
                break;

            case 2:
                removerItemVetor();
                break;

            case 3:
                listarItensVetor();
                break;

            case 4:
                buscarSequencialVetor();
                break;

            case 5:
                ordenarVetor();
                break;

            case 6:
                buscarBinariaVetor();
                break;
        }

    } while(opcao != 0);
}

void menuLista() {

    int opcao;

    do {

        printf("\n===== MOCHILA LISTA =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Voltar\n");

        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {

            case 1:
                inserirItemLista();
                break;

            case 2:
                removerItemLista();
                break;

            case 3:
                listarItensLista();
                break;

            case 4:
                buscarSequencialLista();
                break;
        }

    } while(opcao != 0);
}

//=====================================================
// FUNÇÃO PRINCIPAL
//=====================================================

int main() {

    int opcao;

    do {

        printf("\n===== SISTEMA DE MOCHILA =====\n");
        printf("1 - Mochila com Vetor\n");
        printf("2 - Mochila com Lista Encadeada\n");
        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {

            case 1:
                menuVetor();
                break;

            case 2:
                menuLista();
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}