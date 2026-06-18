#include "csv.h"
#include "ordenacao.h"

int main()
{
    Funcionario vetor[15000];

    int qtd;

    qtd = lerCSV(
        "massaDados.csv",
        vetor
    );

    ordenar(vetor, qtd);

    gerarCSVOrdenado(
        "massaDadosOrdenado.csv",
        vetor,
        qtd
    );

    return 0;
}