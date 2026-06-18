#include <stdio.h>

#include "ordenacao.h"


void quickRec(Funcionario *v,
              int inicio,
              int fim)
{
    int i = inicio;

    int j = fim;


    Funcionario pivo =
    v[(inicio + fim) / 2];


    while (i <= j)
    {
        while (v[i].id < pivo.id)
        {
            i++;
        }

        while (v[j].id > pivo.id)
        {
            j--;
        }


        if (i <= j)
        {
            Funcionario temp;

            temp = v[i];

            v[i] = v[j];

            v[j] = temp;

            i++;

            j--;
        }
    }


    if (inicio < j)
    {
        quickRec(v,
                 inicio,
                 j);
    }


    if (i < fim)
    {
        quickRec(v,
                 i,
                 fim);
    }
}



void quickSort(Funcionario *v,
               int quantidade)
{
    if (quantidade > 1)
    {
        quickRec(v,
                 0,
                 quantidade - 1);
    }
}



void ordenar(Funcionario vetor[],
             int quantidade)
{
    quickSort(vetor,
              quantidade);
}