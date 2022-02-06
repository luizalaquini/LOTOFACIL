#ifndef SISTEMA_H
#define SISTEMA_H

void sist_introducao ();

FILE* sist_carregaArquivo ();

int** sist_leitura (FILE* arquivo);

void sist_exibeRelatorios (float mediaPrimos, float mediaRepeteAnterior, float mediaConsecutivos, int modaPrimos, int modaRepetidos, int modaConsecutivos, float* percPrimos, float* percConsecutivos, float* percRepete);

void extra (int *numeros);

/* LIBERA MEMÓRIA DA MATRIZ PRINCIPAL */
void liberaMatriz (int **matriz);

#endif /* SISTEMA_H */