#ifndef SISTEMA_H
#define SISTEMA_H

/* INTRODUÇÃO BONITINHA */
void sist_introducao ();

/* ABRE ARQUIVO PRA LEITURA */
FILE* sist_carregaArquivo ();

/* LÊ ARQUIVO CSV E RETORNA MATRIZ COM TODOS OS JOGOS REALIZADOS */
int** sist_leitura (FILE* arquivo);

/* IMPRESSÃO DOS PRINCIPAIS RELATÓRIOS */
void sist_exibeRelatorios (float mediaPrimos, float mediaRepeteAnterior, float mediaConsecutivos, int modaPrimos, int modaRepetidos, int modaConsecutivos, float* percPrimos, float* percConsecutivos, float* percRepete);

/* ESTATÍSTICA DE CURIOSIDAE */
void extra (int *numeros);

/* IMPRIME O PERCENTUAL DE JOGOS QUE OBEDECE TODAS AS REGRAS DO GERADOR AO MESMO TEMPO */
void regraGerador (int **matriz);

/* LIBERA MEMÓRIA DA MATRIZ PRINCIPAL */
void liberaMatriz (int **matriz);

#endif /* SISTEMA_H */