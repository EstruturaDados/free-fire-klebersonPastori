#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

//=====================================================
// STRUCT
//=====================================================

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

//=====================================================
// VARIÁVEIS GLOBAIS
//=====================================================

long comparacoes = 0;

//=====================================================
// FUNÇÕES AUXILIARES
//=====================================================

void limparBuffer() {
    while (getchar() != '\n');
}

void mostrarComponentes(Componente vetor[], int tamanho) {

    printf("\n===== COMPONENTES =====\n");

    for(int i = 0; i < tamanho; i++) {
        printf("\nComponente %d\n", i + 1);
        printf("Nome: %s\n", vetor[i].nome);
        printf("Tipo: %s\n", vetor[i].tipo);
        printf("Prioridade: %d\n", vetor[i].prioridade);
    }
}

void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

//=====================================================
// BUBBLE SORT (NOME)
//=====================================================

void bubbleSortNome(Componente vetor[], int tamanho) {

    comparacoes = 0;

    for(int i = 0; i < tamanho - 1; i++) {

        for(int j = 0; j < tamanho - i - 1; j++) {

            comparacoes++;

            if(strcmp(vetor[j].nome,
                      vetor[j + 1].nome) > 0) {

                trocar(&vetor[j],
                       &vetor[j + 1]);
            }
        }
    }
}

//=====================================================
// INSERTION SORT (TIPO)
//=====================================================

void insertionSortTipo(Componente vetor[], int tamanho) {

    comparacoes = 0;

    for(int i = 1; i < tamanho; i++) {

        Componente chave = vetor[i];
        int j = i - 1;

        while(j >= 0) {

            comparacoes++;

            if(strcmp(vetor[j].tipo,
                      chave.tipo) > 0) {

                vetor[j + 1] = vetor[j];
                j--;
            }
            else {
                break;
            }
        }

        vetor[j + 1] = chave;
    }
}

//=====================================================
// SELECTION SORT (PRIORIDADE)
//=====================================================

void selectionSortPrioridade(Componente vetor[],
                             int tamanho) {

    comparacoes = 0;

    for(int i = 0; i < tamanho - 1; i++) {

        int menor = i;

        for(int j = i + 1; j < tamanho; j++) {

            comparacoes++;

            if(vetor[j].prioridade <
               vetor[menor].prioridade) {

                menor = j;
            }
        }

        if(menor != i) {
            trocar(&vetor[i],
                   &vetor[menor]);
        }
    }
}

//=====================================================
// BUSCA BINÁRIA POR NOME
//=====================================================

int buscaBinariaPorNome(Componente vetor[],
                        int tamanho,
                        char chave[]) {

    int inicio = 0;
    int fim = tamanho - 1;

    while(inicio <= fim) {

        int meio = (inicio + fim) / 2;

        int resultado =
            strcmp(vetor[meio].nome,
                   chave);

        if(resultado == 0)
            return meio;

        if(resultado < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

//=====================================================
// MEDIÇÃO DE TEMPO
//=====================================================

double medirTempo(void (*algoritmo)(Componente[], int),
                  Componente vetor[],
                  int tamanho) {

    clock_t inicio = clock();

    algoritmo(vetor, tamanho);

    clock_t fim = clock();

    return ((double)(fim - inicio))
            / CLOCKS_PER_SEC;
}

//=====================================================
// MAIN
//=====================================================

int main() {

    Componente componentes[MAX_COMPONENTES];
    int quantidade;

    printf("Quantidade de componentes (max 20): ");
    scanf("%d", &quantidade);
    limparBuffer();

    if(quantidade < 1 || quantidade > 20) {
        printf("Quantidade invalida!\n");
        return 0;
    }

    for(int i = 0; i < quantidade; i++) {

        printf("\n=== Componente %d ===\n",
               i + 1);

        printf("Nome: ");
        fgets(componentes[i].nome,
              30,
              stdin);
        componentes[i].nome[
            strcspn(componentes[i].nome,
                    "\n")] = '\0';

        printf("Tipo: ");
        fgets(componentes[i].tipo,
              20,
              stdin);
        componentes[i].tipo[
            strcspn(componentes[i].tipo,
                    "\n")] = '\0';

        printf("Prioridade (1-10): ");
        scanf("%d",
              &componentes[i].prioridade);

        limparBuffer();
    }

    int opcao;

    do {

        printf("\n===== MENU =====\n");
        printf("1 - Bubble Sort (Nome)\n");
        printf("2 - Insertion Sort (Tipo)\n");
        printf("3 - Selection Sort (Prioridade)\n");
        printf("4 - Busca Binaria por Nome\n");
        printf("5 - Mostrar Componentes\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        scanf("%d", &opcao);
        limparBuffer();

        double tempo;
        char chave[30];
        int posicao;

        switch(opcao) {

            case 1:

                tempo = medirTempo(
                            bubbleSortNome,
                            componentes,
                            quantidade);

                printf("\nOrdenado por Nome!\n");
                printf("Comparacoes: %ld\n",
                       comparacoes);
                printf("Tempo: %.8f segundos\n",
                       tempo);

                mostrarComponentes(
                    componentes,
                    quantidade);

                break;

            case 2:

                tempo = medirTempo(
                            insertionSortTipo,
                            componentes,
                            quantidade);

                printf("\nOrdenado por Tipo!\n");
                printf("Comparacoes: %ld\n",
                       comparacoes);
                printf("Tempo: %.8f segundos\n",
                       tempo);

                mostrarComponentes(
                    componentes,
                    quantidade);

                break;

            case 3:

                tempo = medirTempo(
                            selectionSortPrioridade,
                            componentes,
                            quantidade);

                printf("\nOrdenado por Prioridade!\n");
                printf("Comparacoes: %ld\n",
                       comparacoes);
                printf("Tempo: %.8f segundos\n",
                       tempo);

                mostrarComponentes(
                    componentes,
                    quantidade);

                break;

            case 4:

                printf("\nDigite o nome do componente-chave: ");

                fgets(chave, 30, stdin);

                chave[
                    strcspn(chave, "\n")
                ] = '\0';

                posicao =
                    buscaBinariaPorNome(
                        componentes,
                        quantidade,
                        chave);

                if(posicao != -1) {

                    printf(
                        "\nComponente encontrado!\n");

                    printf(
                        "Nome: %s\n",
                        componentes[posicao].nome);

                    printf(
                        "Tipo: %s\n",
                        componentes[posicao].tipo);

                    printf(
                        "Prioridade: %d\n",
                        componentes[posicao].prioridade);

                    printf(
                        "\nTorre pronta para ativacao!\n");
                }
                else {

                    printf(
                        "\nComponente nao encontrado!\n");
                }

                break;

            case 5:

                mostrarComponentes(
                    componentes,
                    quantidade);

                break;

            case 0:

                printf(
                    "\nEncerrando sistema...\n");

                break;

            default:

                printf(
                    "\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}