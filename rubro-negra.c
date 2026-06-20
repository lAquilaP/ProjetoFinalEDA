#include <stdio.h>
#include <stdlib.h>
#include "rubro_negra.h"

#define RED 1
#define BLACK 0

int corNo(struct NO *H) {
    if (H == NULL) {
        return BLACK;
    } else {
        return H->cor;
    }
}
 
void trocaCor(struct NO *H) {
    H->cor = !H->cor;
    if (H->esq != NULL) {
        H->esq->cor = !H->esq->cor;
    }
    if (H->dir != NULL) {
        H->dir->cor = !H->dir->cor;
    }
}
 
struct NO *rotacionaEsquerda(struct NO *A) {
    struct NO *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}
 
struct NO *rotacionaDireita(struct NO *A) {
    struct NO *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

static rubro_negra novoNo(Funcionario f) {
    rubro_negra novo = (rubro_negra) malloc(sizeof(struct NO));
    if (novo == NULL) {
        fprintf(stderr, "Erro: falha na alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }
    novo->info = f;
    novo->esq  = NULL;
    novo->dir  = NULL;
    novo->cor  = RED;
    return novo;
}
 
rubro_negra inserirRubroNegra(rubro_negra H, Funcionario f) {
 
    if (H == NULL) {
        return novoNo(f);
    }
 
    if (f.id < H->info.id) {
        H->esq = inserirRubroNegra(H->esq, f);
    } else if (f.id > H->info.id) {
        H->dir = inserirRubroNegra(H->dir, f);
    }
 
    if (corNo(H->dir) == RED && corNo(H->esq) != RED) {
        H = rotacaoEsq(H);
    }
 
    if (corNo(H->esq) == RED && corNo(H->esq->esq) == RED) {
        H = rotacaoDireita(H);
    }
 
    if (corNo(H->esq) == RED && corNo(H->dir) == RED) {
        trocaCor(H);
    }
 
    return H;
}

void imprimirRubroNegra(rubro_negra H) {
    if (H == NULL) return;
    imprimirRubroNegra(H->esq);
    printf("ID: %d\nNome: %s\nIdade: %d\nEmpresa: %s\nDepto: %s\nSalario: %.2f\n\n",
           H->info.id,
           H->info.nome,
           H->info.idade,
           H->info.empresa,
           H->info.departamento,
           H->info.salario);
    imprimirRubroNegra(H->dir);
}
 
void liberarRubroNegra(rubro_negra H) {
    if (H == NULL) return;
    liberarRubroNegra(H->esq);
    liberarRubroNegra(H->dir);
    free(H);
}