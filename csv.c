#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"


int lerCSV(const char *nomeArquivo,
           Funcionario vetor[])
{
    FILE *arquivo;

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir %s\n",
               nomeArquivo);

        return 0;
    }


    char linha[300];

    int quantidade = 0;


    /* Ignora o cabeçalho */

    fgets(linha,
          sizeof(linha),
          arquivo);


    while (fgets(linha,
                 sizeof(linha),
                 arquivo))
    {
        char *token;


        /* ID */

        token = strtok(linha, ";");

        vetor[quantidade].id =
        atoi(token);


        /* Nome */

        token = strtok(NULL, ";");

        strcpy(vetor[quantidade].nome,
               token);


        /* Idade */

        token = strtok(NULL, ";");

        vetor[quantidade].idade =
        atoi(token);


        /* Empresa */

        token = strtok(NULL, ";");

        strcpy(vetor[quantidade].empresa,
               token);


        /* Departamento */

        token = strtok(NULL, ";");

        strcpy(vetor[quantidade].departamento,
               token);


        /* Salário */

        token = strtok(NULL, "\n");


        /* troca vírgula por ponto */

        for(int i = 0;
            token[i] != '\0';
            i++)
        {
            if(token[i] == ',')
            {
                token[i] = '.';
            }
        }


        vetor[quantidade].salario =
        atof(token);


        quantidade++;
    }


    fclose(arquivo);

    return quantidade;
}



void gerarCSVOrdenado(
        const char *nomeArquivo,

        Funcionario vetor[],

        int quantidade)
{
    FILE *arquivo;

    arquivo = fopen(nomeArquivo, "w");


    if(arquivo == NULL)
    {
        printf("Erro ao criar arquivo.\n");

        return;
    }


    fprintf(arquivo,

    "ID;Nome;Idade;Empresa;Departamento;Salario\n");


    for(int i = 0;
        i < quantidade;
        i++)
    {
        fprintf(arquivo,

        "%d;%s;%d;%s;%s;%.2f\n",

        vetor[i].id,

        vetor[i].nome,

        vetor[i].idade,

        vetor[i].empresa,

        vetor[i].departamento,

        vetor[i].salario
        );
    }


    fclose(arquivo);
}