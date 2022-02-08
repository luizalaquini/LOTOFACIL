#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

/* RETORNA VERDADEIRO SE O NÚMERO PASSADO COMO ARGUMENTO FOR PRIMO */
int EhPrimo (int num);

/* RETORNA VERDADEIRO SE O NÚMERO B FOR CONSECUTIVO DO NÚMERO A */
int EhConsecutivo (int a, int b);

/* FAZ O CÁLCULO DA MÉDIA DE VALORES DE UM VETOR */
float calculaMedia (int *vetor);

/* FAZ O CÁLCULO DA MODA DE VALORES DE UM VETOR */
int calculaModa (int *vetor);

/* FAZ O CÁLCULO DO PERCENTUAL DE VALORES DE UM VETOR */
float* calculaPercentual (int *vetor);

#endif /* ESTATISTICAS_H */