#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


int obterAltura(NoAVL *no) {
    if (no == NULL) {
        return 0;
    }
    return no->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int obterFatorBalanceamento(NoAVL *no) {
    if (no == NULL) {
        return 0;
    }
    return obterAltura(no->esq) - obterAltura(no->dir);
}

NoAVL* criarNoAVL(Funcionario f) {
    NoAVL *novoNo = (NoAVL*)malloc(sizeof(NoAVL));
    novoNo->dados = f;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->altura = 1; 
    return novoNo;
}

NoAVL* rotacionarDireita(NoAVL *y) {
    NoAVL *x = y->esq;
    NoAVL *T2 = x->dir;

  
    x->dir = y;
    y->esq = T2;

    
    y->altura = max(obterAltura(y->esq), obterAltura(y->dir)) + 1;
    x->altura = max(obterAltura(x->esq), obterAltura(x->dir)) + 1;

    return x;
}

NoAVL* rotacionarEsquerda(NoAVL *x) {
    NoAVL *y = x->dir;
    NoAVL *T2 = y->esq;

  
    y->esq = x;
    x->dir = T2;

    x->altura = max(obterAltura(x->esq), obterAltura(x->dir)) + 1;
    y->altura = max(obterAltura(y->esq), obterAltura(y->dir)) + 1;

    return y;
}

NoAVL* inserirAVL(NoAVL *no, Funcionario f) {

    if (no == NULL) {
        return criarNoAVL(f);
    }

    if (f.id < no->dados.id) {
        no->esq = inserirAVL(no->esq, f);
    } 
    else if (f.id > no->dados.id) {
        no->dir = inserirAVL(no->dir, f);
    } 
    else {
        
        return no;
    }

    no->altura = 1 + max(obterAltura(no->esq), obterAltura(no->dir));

    int fator = obterFatorBalanceamento(no);

    if (fator > 1 && f.id < no->esq->dados.id) {
        return rotacionarDireita(no);
    }

    if (fator < -1 && f.id > no->dir->dados.id) {
        return rotacionarEsquerda(no);
    }

    if (fator > 1 && f.id > no->esq->dados.id) {
        no->esq = rotacionarEsquerda(no->esq);
        return rotacionarDireita(no);
    }

    if (fator < -1 && f.id < no->dir->dados.id) {
        no->dir = rotacionarDireita(no->dir);
        return rotacionarEsquerda(no);
    }

    return no;
}