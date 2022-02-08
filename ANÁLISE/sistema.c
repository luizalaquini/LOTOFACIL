#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sistema.h"
#include "estatisticas.h"

#define LINHA 2442 // ######################### IMPORTANTE
#define COLUNA 15
#define NUM_BOLAS 25

void sist_introducao (){
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("---------------------------------------- ANÁLISE ESTATÍSTICA DA LOTOFÁCIL ----------------------------------------\n");
    printf("---------------------------------------------- By: Luiza B. Laquini ----------------------------------------------\n\n");
}

FILE* sist_carregaArquivo (){
    FILE* arquivo = fopen("2442.csv", "r"); // ######################### IMPORTANTE

    if(arquivo == NULL) printf("Erro ao carregar o arquivo!\n"); 
    else printf("- Arquivo aberto com sucesso!\n");

    return arquivo;
} 

int** sist_leitura (FILE* arquivo){
    int **matriz = (int**) malloc (LINHA * sizeof(int*));

    for (int i=0; i<LINHA; i++){
        matriz[i] = (int*) malloc (COLUNA * sizeof(int));
    }

    for(int i=0; i<LINHA; i++){ // armazenando números de todos os sorteios
        for(int j=0; j<COLUNA; j++){
            if(j<14) fscanf(arquivo, "%d,", &matriz[i][j]);
            else fscanf(arquivo, "%d", &matriz[i][j]); // a diferença está na vírgula
        }
    }

    fclose(arquivo);
    printf("- Arquivo fechado\n");
    printf("- Número de sorteios computados: %d\n\n", LINHA);
    printf("------------------------------------------------------------------------------------------------------------------\n");

    return matriz;
}

void sist_exibeRelatorios (float mediaPrimos, float mediaRepeteAnterior, float mediaConsecutivos, int modaPrimos, int modaRepetidos, int modaConsecutivos, float* percPrimos, float* percConsecutivos, float* percRepete){
    printf("RELATÓRIOS\n");
    printf("------------------------------------------------------------------------------------------------------------------\n\n");
    printf("Acerca dos números PRIMOS por sorteio:\n\n");
    printf("MÉDIA: %.2f\n", mediaPrimos);
    printf("MODA: %d\n", modaPrimos);
    printf("PERCENTUAIS: 0(%.2f) | 1(%.2f) | 2(%.2f) | 3(%.2f) | 4(%.2f) | 5(%.2f) | 6(%.2f) | 7(%.2f) | 8(%.2f) | 9(%.2f)\n", percPrimos[0], percPrimos[1], percPrimos[2], percPrimos[3], percPrimos[4], percPrimos[5], percPrimos[6], percPrimos[7], percPrimos[8], percPrimos[9]);
    printf("------------------------------------------------------------------------------------------------------------------\n\n");
    printf("Acerca dos números REPETIDOS por sorteio (em relação ao sorteio anterior):\n\n");
    printf("MÉDIA: %.2f\n", mediaRepeteAnterior);
    printf("MODA: %d\n", modaRepetidos);
    printf("PERCENTUAIS: 5(%.2f) | 6(%.2f) | 7(%.2f) | 8(%.2f) | 9(%.2f) | 10(%.2f) | 11(%.2f) | 12(%.2f) | 13(%.2f) | 14(%.2f) | 15(%.2f)\n", percRepete[4], percRepete[5], percRepete[6], percRepete[7], percRepete[8], percRepete[9], percRepete[10], percRepete[11], percRepete[12], percRepete[13], percRepete[14]);
    printf("------------------------------------------------------------------------------------------------------------------\n\n");
    printf("Acerca da maior sequência de números CONSECUTIVOS por sorteio:\n\n");
    printf("MÉDIA: %.2f\n", mediaConsecutivos);
    printf("MODA: %d\n", modaConsecutivos);
    printf("PERCENTUAIS: 1(%.2f) | 2(%.2f) | 3(%.2f) | 4(%.2f) | 5(%.2f) | 6(%.2f) | 7(%.2f) | 8(%.2f) | 9(%.2f) | 10(%.2f) | 11(%.2f) | 12(%.2f) | 13(%.2f) | 14(%.2f) | 15(%.2f)\n", percConsecutivos[0], percConsecutivos[1], percConsecutivos[2], percConsecutivos[3], percConsecutivos[4], percConsecutivos[5], percConsecutivos[6], percConsecutivos[7], percConsecutivos[8], percConsecutivos[9], percConsecutivos[10], percConsecutivos[11], percConsecutivos[12], percConsecutivos[13], percConsecutivos[14]);
    printf("------------------------------------------------------------------------------------------------------------------\n\n");
}

void extra (int *numeros){
    printf("EXTRA: Quantas vezes saiu cada número...\n\n");
    printf("| NÚMERO | Quantas vezes foi sorteado |\n");
    
    for (int i=0; i<NUM_BOLAS; i++){
        printf("|   %.2d   |            %d            |\n", (i+1), numeros[i]);
        printf("|--------|----------------------------|\n");
    } 
}

void liberaMatriz (int **matriz){
    for (int i=0; i<LINHA; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void regraGerador (int **matriz){
    int obedeceTudo = 0;
    bool obedecePrimo = false, obedeceConsecutivos = false, obedeceRepetidos = false;
    float resultado;

    // Vamos percorrer a matriz de sorteios novamente conferindo e contando cada jogo que obedeça TODAS as regras ao mesmo tempo
    for (int i=0; i<LINHA; i++){
        int primos = 0;
        int consecutivos = 1, maior = 0;
        int repetidos = 0;

        int anterior[COLUNA];
        if(i < LINHA-1){ // p nao estourar
            for (int k=0; k<COLUNA; k++){
                anterior[k] = matriz[i+1][k];
            } 
        }
        
        for (int j=0; j<COLUNA; j++){
            bool achou = false;

            if(EhPrimo(matriz[i][j])) primos++; 

            for (int k=0; k<COLUNA; k++){ // Consecutivo
                if(EhConsecutivo(matriz[i][j], matriz[i][k])){
                    consecutivos++;
                    achou = true;
                }
            }
            if (achou == false){
                if (consecutivos > maior) maior = consecutivos;
                consecutivos = 1;
            }

            if (i < LINHA-1){ // EhRepetido
                for (int k=0; k<COLUNA; k++){
                    if (matriz[i][j] == anterior[k]) repetidos++; 
                }
            }
        }

        //printf("PRIMOS = %d CONSECUTIVOS = %d REPETIDOS = %d\n", primos, maior, repetidos);

        /* A REGRA (teste)
        * 4 a 6 números primos
        * 3 a 5 números consecutivos (maior sequencia de consecutivos)
        * 7 a 10 números repetidos em relação ao sorteio anterior
        */

        if(primos >= 4 && primos <= 6) obedecePrimo = true;
        else obedecePrimo = false;

        if (maior >= 3 && maior <= 6) obedeceConsecutivos = true;
        else obedeceConsecutivos = false;

        if (repetidos >= 7 && repetidos <= 10) obedeceRepetidos = true;
        else obedeceConsecutivos = false;

        if(obedecePrimo == true && obedeceConsecutivos == true && obedeceRepetidos == true) obedeceTudo++;
    }

    //printf("\nobedeceTudo = %d\n", obedeceTudo);

    resultado = (obedeceTudo * 100.0) / LINHA;
    printf("A REGRA SUGERIDA:\n");
    printf("3 a 4 números primos\n");
    printf("3 a 5 números consecutivos (maior sequência)\n");
    printf("7 a 10 números repetidos em relação ao sorteio anterior\n\n");

    printf("%.2f%% DOS JOGOS OBEDECEM TODAS AS REGRAS AO MESMO TEMPO (%d DE %d)\n", resultado, obedeceTudo, LINHA);
    printf("------------------------------------------------------------------------------------------------------------------\n\n");
}