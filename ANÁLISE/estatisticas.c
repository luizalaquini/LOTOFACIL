#include <stdio.h>
#include <stdlib.h>
#include "estatisticas.h"

#define LINHA 2442 // ######################### IMPORTANTE
#define COLUNA 15
#define NUM_BOLAS 25
#define MAX_PRIMOS 9

int EhPrimo (int num){
    if (num == 2 || num == 3 || num == 5 || num == 7 || num == 11 || num == 13 || num == 17 || num == 19 || num == 23) return 1;
    else return 0;
}

int EhConsecutivo (int a, int b){
    if (a + 1 == b) return 1;
    else return 0;
}

float calculaMedia (int *vetor){
    float result = 0;

    for(int i=0; i<LINHA; i++){
        result += vetor[i];
    }

    result /= LINHA;

    return result;
}

int calculaModa (int *vetor){
    int num, maior = 0;
    int qtds[NUM_BOLAS];

    for (int i=0; i<NUM_BOLAS; i++) // zerando
        qtds[i] = 0;

    for(int i=0; i<LINHA; i++) // contagem das quantidades de cada num
        qtds[vetor[i]-1]++;
    for(int i=0; i<NUM_BOLAS; i++){ // verifica resposta
        if (qtds[i] > maior){
            maior = qtds[i];
            num = i+1;
        } 
    }

    return num;
}

float* calculaPercentual (int *vetor){
    float *percents = (float*) malloc (NUM_BOLAS * sizeof(float)); 
    int total = 0;

    for (int i=0; i<NUM_BOLAS; i++){ // zerando
        percents[i] = 0.0;
    }

    for(int i=0; i<NUM_BOLAS; i++) // contagem do totalzao que vai representar 100%
        total += vetor[i];

    for(int i=0; i<NUM_BOLAS; i++){ // calculando percentuais
        percents[i] = (vetor[i] * 100.0) / total;
    }

    return percents;
}