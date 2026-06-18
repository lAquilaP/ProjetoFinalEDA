#ifndef CSV_H
#define CSV_H

#define TAM_NOME 120
#define TAM_EMPRESA 120
#define TAM_DEPARTAMENTO 120

typedef struct
{
    int id;

    char nome[TAM_NOME];

    int idade;

    char empresa[TAM_EMPRESA];

    char departamento[TAM_DEPARTAMENTO];

    float salario;

} Funcionario;


int lerCSV(const char *nomeArquivo,
           Funcionario vetor[]);


void gerarCSVOrdenado(const char *nomeArquivo,
                      Funcionario vetor[],
                      int quantidade);

#endif