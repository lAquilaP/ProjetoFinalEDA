#include "testes.h"

#include "avl.h"
#include "csv.h"
#include "ordenacao.h"
#include "rubro_negra.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_FUNCIONARIOS 15000
#define ARQUIVO_ENTRADA "massaDados.csv"

static NoAVL *montarAVL(Funcionario vetor[], int quantidade)
{
    NoAVL *raiz = NULL;

    for (int i = 0; i < quantidade; i++)
    {
        raiz = inserirAVL(raiz, vetor[i]);
    }

    return raiz;
}

static rubro_negra montarRubroNegra(Funcionario vetor[], int quantidade)
{
    rubro_negra raiz = NULL;

    for (int i = 0; i < quantidade; i++)
    {
        raiz = inserirRubroNegra(raiz, vetor[i]);

        if (raiz != NULL)
        {
            raiz->cor = 0;
        }
    }

    return raiz;
}

static void liberarAVL(NoAVL *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    liberarAVL(raiz->esq);
    liberarAVL(raiz->dir);
    free(raiz);
}

static int vetorOrdenadoPorId(Funcionario vetor[], int quantidade)
{
    for (int i = 1; i < quantidade; i++)
    {
        if (vetor[i - 1].id > vetor[i].id)
        {
            return 0;
        }
    }

    return 1;
}

static int contarNosAVL(NoAVL *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    return 1 + contarNosAVL(raiz->esq) + contarNosAVL(raiz->dir);
}

static int validarAVL(NoAVL *raiz)
{
    int fator;

    if (raiz == NULL)
    {
        return 1;
    }

    fator = obterFatorBalanceamento(raiz);

    if (fator < -1 || fator > 1)
    {
        return 0;
    }

    return validarAVL(raiz->esq) && validarAVL(raiz->dir);
}

static int contarNosRubroNegra(rubro_negra raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    return 1 + contarNosRubroNegra(raiz->esq) + contarNosRubroNegra(raiz->dir);
}

static void registrarTeste(const char *nome, int passou, int *total, int *aprovados)
{
    (*total)++;

    if (passou)
    {
        (*aprovados)++;
        printf("[OK]    %s\n", nome);
    }
    else
    {
        printf("[FALHA] %s\n", nome);
    }
}

void executarTestes(void)
{
    Funcionario amostra[] = {
        {40, "Ana", 31, "A", "TI", 5000.0f},
        {10, "Bia", 27, "B", "RH", 4300.0f},
        {30, "Caio", 42, "C", "Financeiro", 7100.0f},
        {20, "Davi", 35, "D", "Vendas", 3900.0f},
        {50, "Eva", 29, "E", "TI", 6200.0f}
    };
    static Funcionario dadosArquivo[MAX_FUNCIONARIOS];
    int quantidadeAmostra = (int)(sizeof(amostra) / sizeof(amostra[0]));
    int quantidadeArquivo;
    NoAVL *avl;
    rubro_negra rn;
    int total = 0;
    int aprovados = 0;

    printf("\n========== TESTES ==========\n");

    quantidadeArquivo = lerCSV(ARQUIVO_ENTRADA, dadosArquivo);
    registrarTeste("Leitura do CSV principal", quantidadeArquivo > 0, &total, &aprovados);

    ordenar(amostra, quantidadeAmostra);
    registrarTeste("Ordenacao por ID", vetorOrdenadoPorId(amostra, quantidadeAmostra), &total, &aprovados);

    avl = montarAVL(amostra, quantidadeAmostra);
    registrarTeste("Insercao AVL preserva quantidade", contarNosAVL(avl) == quantidadeAmostra, &total, &aprovados);
    registrarTeste("AVL permanece balanceada", validarAVL(avl), &total, &aprovados);
    liberarAVL(avl);

    rn = montarRubroNegra(amostra, quantidadeAmostra);
    registrarTeste("Insercao Rubro-Negra preserva quantidade", contarNosRubroNegra(rn) == quantidadeAmostra, &total, &aprovados);
    registrarTeste("Raiz Rubro-Negra fica preta", rn == NULL || rn->cor == 0, &total, &aprovados);
    liberarRubroNegra(rn);

    printf("\nResultado: %d/%d testes aprovados.\n", aprovados, total);
}
