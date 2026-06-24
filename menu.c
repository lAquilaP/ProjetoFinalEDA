#include "menu.h"

#include "avl.h"
#include "csv.h"
#include "ordenacao.h"
#include "rubro_negra.h"
#include "testes.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FUNCIONARIOS 15000
#define ARQUIVO_DESORDENADO "massaDados.csv"
#define ARQUIVO_ORDENADO "massaDadosOrdenado.csv"

typedef enum
{
    ARVORE_AVL,
    ARVORE_RUBRO_NEGRA
} TipoArvore;

static double segundosDecorridos(clock_t inicio, clock_t fim)
{
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

static void pausar(void)
{
    printf("\nPressione ENTER para continuar...");
    getchar();
}

static void limparEntrada(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

static int lerOpcao(void)
{
    int opcao;

    printf("\nOpcao: ");

    if (scanf("%d", &opcao) != 1)
    {
        limparEntrada();
        return -1;
    }

    limparEntrada();
    return opcao;
}

static void exibirMenu(void)
{
    printf("\n========== MENU ==========\n");
    printf("1 - Gerar arquivo ordenado\n");
    printf("2 - Medir AVL com dados desordenados\n");
    printf("3 - Medir Rubro-Negra com dados desordenados\n");
    printf("4 - Medir AVL com dados ordenados\n");
    printf("5 - Medir Rubro-Negra com dados ordenados\n");
    printf("6 - Executar comparativo completo\n");
    printf("7 - Executar testes automaticos\n");
    printf("0 - Sair\n");
}

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

static int arquivoExiste(const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        return 0;
    }

    fclose(arquivo);
    return 1;
}

static void gerarArquivoOrdenado(void)
{
    static Funcionario vetor[MAX_FUNCIONARIOS];
    clock_t inicio;
    clock_t fim;
    int quantidade;

    printf("\nGerando arquivo ordenado a partir de %s...\n", ARQUIVO_DESORDENADO);

    inicio = clock();
    quantidade = lerCSV(ARQUIVO_DESORDENADO, vetor);
    fim = clock();
    printf("Leitura: %d registros em %.6f segundos.\n",
           quantidade,
           segundosDecorridos(inicio, fim));

    if (quantidade <= 0)
    {
        printf("Nao foi possivel gerar o arquivo ordenado.\n");
        return;
    }

    inicio = clock();
    ordenar(vetor, quantidade);
    fim = clock();
    printf("Ordenacao: %.6f segundos.\n", segundosDecorridos(inicio, fim));

    inicio = clock();
    gerarCSVOrdenado(ARQUIVO_ORDENADO, vetor, quantidade);
    fim = clock();
    printf("Gravacao de %s: %.6f segundos.\n",
           ARQUIVO_ORDENADO,
           segundosDecorridos(inicio, fim));

    printf("Arquivo ordenado gerado com sucesso.\n");
}

static void garantirArquivoOrdenado(void)
{
    if (!arquivoExiste(ARQUIVO_ORDENADO))
    {
        printf("\n%s ainda nao existe.\n", ARQUIVO_ORDENADO);
        gerarArquivoOrdenado();
    }
}

static double medirLeituraEInsercao(const char *nomeArquivo,
                                    TipoArvore tipo,
                                    int *quantidade)
{
    static Funcionario vetor[MAX_FUNCIONARIOS];
    NoAVL *raizAVL = NULL;
    rubro_negra raizRubroNegra = NULL;
    clock_t inicio;
    clock_t fim;

    inicio = clock();
    *quantidade = lerCSV(nomeArquivo, vetor);

    if (*quantidade <= 0)
    {
        fim = clock();
        return segundosDecorridos(inicio, fim);
    }

    if (tipo == ARVORE_AVL)
    {
        raizAVL = montarAVL(vetor, *quantidade);
        fim = clock();
        liberarAVL(raizAVL);
    }
    else
    {
        raizRubroNegra = montarRubroNegra(vetor, *quantidade);
        fim = clock();
        liberarRubroNegra(raizRubroNegra);
    }

    return segundosDecorridos(inicio, fim);
}

static void exibirResultado(const char *nomeArvore,
                            const char *tipoDados,
                            const char *nomeArquivo,
                            int quantidade,
                            double tempo)
{
    printf("\nArvore: %s\n", nomeArvore);
    printf("Dados: %s\n", tipoDados);
    printf("Arquivo: %s\n", nomeArquivo);
    printf("Registros inseridos: %d\n", quantidade);
    printf("Tempo total (leitura + insercao): %.6f segundos.\n", tempo);
}

static double executarMedicao(const char *nomeArquivo,
                              const char *tipoDados,
                              TipoArvore tipo)
{
    const char *nomeArvore = (tipo == ARVORE_AVL) ? "AVL" : "Rubro-Negra";
    int quantidade = 0;
    double tempo;

    tempo = medirLeituraEInsercao(nomeArquivo, tipo, &quantidade);
    exibirResultado(nomeArvore, tipoDados, nomeArquivo, quantidade, tempo);

    return tempo;
}

static void executarMedicaoOrdenada(TipoArvore tipo)
{
    garantirArquivoOrdenado();

    if (arquivoExiste(ARQUIVO_ORDENADO))
    {
        executarMedicao(ARQUIVO_ORDENADO, "ordenados", tipo);
    }
}

static void executarComparativoCompleto(void)
{
    double avlDesordenado;
    double rnDesordenado;
    double avlOrdenado;
    double rnOrdenado;

    gerarArquivoOrdenado();

    printf("\n========== COMPARATIVO ==========\n");
    avlDesordenado = executarMedicao(ARQUIVO_DESORDENADO, "desordenados", ARVORE_AVL);
    rnDesordenado = executarMedicao(ARQUIVO_DESORDENADO, "desordenados", ARVORE_RUBRO_NEGRA);
    avlOrdenado = executarMedicao(ARQUIVO_ORDENADO, "ordenados", ARVORE_AVL);
    rnOrdenado = executarMedicao(ARQUIVO_ORDENADO, "ordenados", ARVORE_RUBRO_NEGRA);

    printf("\n========== RESUMO ==========\n");
    printf("AVL          | desordenados | %.6f s\n", avlDesordenado);
    printf("Rubro-Negra  | desordenados | %.6f s\n", rnDesordenado);
    printf("AVL          | ordenados    | %.6f s\n", avlOrdenado);
    printf("Rubro-Negra  | ordenados    | %.6f s\n", rnOrdenado);
}

void executarMenu(void)
{
    int opcao;

    do
    {
        exibirMenu();
        opcao = lerOpcao();

        switch (opcao)
        {
            case 1:
                gerarArquivoOrdenado();
                pausar();
                break;

            case 2:
                executarMedicao(ARQUIVO_DESORDENADO, "desordenados", ARVORE_AVL);
                pausar();
                break;

            case 3:
                executarMedicao(ARQUIVO_DESORDENADO, "desordenados", ARVORE_RUBRO_NEGRA);
                pausar();
                break;

            case 4:
                executarMedicaoOrdenada(ARVORE_AVL);
                pausar();
                break;

            case 5:
                executarMedicaoOrdenada(ARVORE_RUBRO_NEGRA);
                pausar();
                break;

            case 6:
                executarComparativoCompleto();
                pausar();
                break;

            case 7:
                executarTestes();
                pausar();
                break;

            case 0:
                printf("\nEncerrando o programa.\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
                pausar();
                break;
        }
    }
    while (opcao != 0);
}
