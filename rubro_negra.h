#include "csv.h"

typedef struct NO *rubro_negra;

struct NO{
    Funcionario info;
    struct NO *esq;
    struct NO *dir;
    int cor;
};

int corNo(rubro_negra H);
void trocaCor(rubro_negra H);
rubro_negra rotacionaEsquerda(rubro_negra H);
rubro_negra rotacionaDireita(rubro_negra H);

rubro_negra inserirRubroNegra(rubro_negra H, Funcionario f);
void imprimirRubroNegra(rubro_negra H);
void liberarRubroNegra(rubro_negra H);