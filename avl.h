#ifndef AVL_H
#define AVL_H

#include "csv.h"

typedef struct NoAVL {
    Funcionario dados;     
    int altura;            
    struct NoAVL *esq;
    struct NoAVL *dir;
} NoAVL;

int obterAltura(NoAVL *no);
int max(int a, int b);
int obterFatorBalanceamento(NoAVL *no);
NoAVL* criarNoAVL(Funcionario f);

NoAVL* rotacionarDireita(NoAVL *y);
NoAVL* rotacionarEsquerda(NoAVL *x);

NoAVL* inserirAVL(NoAVL *no, Funcionario f);

#endif