#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "csv.h"


void quickRec(Funcionario *v,
              int inicio,
              int fim);


void quickSort(Funcionario *v,
               int quantidade);


void ordenar(Funcionario vetor[],
             int quantidade);

#endif