#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca pecas[TAM_FILA];
    int frente;
    int tras;
    int tamanho;
} FilaCircular;

void enqueue(FilaCircular *fila);
Peca gerarPeca();

int filaVazia(FilaCircular fila) {
    return fila.tamanho == 0;
}

int filaCheia(FilaCircular fila) {
    return fila.tamanho == TAM_FILA;
}

Peca gerarPeca() {
    Peca novaPeca;
    static int proximoId = 0;
    char tipos[] = {'I', 'O', 'T', 'L'};

    novaPeca.tipo = tipos[rand() % 4];
    novaPeca.id = proximoId++;
    return novaPeca;
}

void inicializarFila(FilaCircular *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(fila);
    }
}

void enqueue(FilaCircular *fila) {
    if (filaCheia(*fila)) {
        return;
    }
    Peca novaPeca = gerarPeca();
    fila->tras = (fila->tras + 1) % TAM_FILA;
    fila->pecas[fila->tras] = novaPeca;
    fila->tamanho++;
}

void dequeue(FilaCircular *fila) {
    if (filaVazia(*fila)) {
        printf("\n>> ERRO: A fila esta vazia. Nao e possivel remover pecas.\n");
        return;
    }

    Peca pecaRemovida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % TAM_FILA;
    fila->tamanho--;
    printf("\n>> Peca [%c %d] removida da fila.\n", pecaRemovida.tipo, pecaRemovida.id);

    enqueue(fila);
    printf(">> Uma nova peca foi gerada e inserida na fila.\n");
}

void mostrarFila(FilaCircular fila) {
    printf("\n----------------------------------------\n");
    printf("Fila de Pecas: ");
    if (filaVazia(fila)) {
        printf("Fila vazia.\n");
    } else {
        int i = fila.frente;
        for (int c = 0; c < fila.tamanho; c++) {
            printf("[%c %d] ", fila.pecas[i].tipo, fila.pecas[i].id);
            i = (i + 1) % TAM_FILA;
        }
        printf("\n");
    }
    printf("----------------------------------------\n");
}

void exibirMenu() {
    printf("\nOpcoes:\n");
    printf("  1 - Jogar peca (remover da frente)\n");
    printf("  0 - Sair\n");
    printf("Digite sua opcao: ");
}

int main() {
    srand(time(NULL));

    FilaCircular filaDePecas;
    inicializarFila(&filaDePecas);

    int opcao;

    do {
        mostrarFila(filaDePecas);
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&filaDePecas);
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\n>> Opcao invalida. Por favor, tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
