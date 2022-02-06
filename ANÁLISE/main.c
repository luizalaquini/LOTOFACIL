#include <stdio.h>
#include <stdlib.h>
#include "estatisticas.h"
#include "sistema.h"

#define LINHA 2440 // ######################### IMPORTANTE
#define COLUNA 15
#define NUM_BOLAS 25
#define MAX_PRIMOS 9

int main (){

    sist_introducao();

    // DECLARANDO VARIÁVEIS NECESSÁRIAS
    
    int vetorQtdPrimos[LINHA], vetorQtdConsecutivos[LINHA], vetorQtdRepeteAnterior[LINHA]; // vetores de análise para as MÉDIAS e MODAS
    int vetorQtdNumPrimos[NUM_BOLAS], vetorQtdNumConsec[NUM_BOLAS], vetorQtdNumRepete[NUM_BOLAS]; // vetores de análise para os PERCENTUAIS
    int vetorA[NUM_BOLAS], vetorB[NUM_BOLAS], vetorC[NUM_BOLAS]; // vetores auxiliares 
    int qtdCadaNum[NUM_BOLAS]; // conta quantas vezes saiu cada número (sessão extra)
    int cont = 1, maior = 0; // variaveis auxiliares (contadores) 

    for(int i=0; i<LINHA; i++){ // zerando
        vetorQtdPrimos[i] = 0;
        vetorQtdConsecutivos[i] = 0;
        vetorQtdRepeteAnterior[i] = 0;
        if(i<NUM_BOLAS){
            vetorQtdNumPrimos[i] = 0;
            vetorQtdNumConsec[i] = 0;
            vetorA[i] = 0;
            vetorB[i] = 0;
            vetorC[i] = 0;
            qtdCadaNum[i] = 0;
        }
    }

    // LEITURA DO ARQUIVO 
    FILE* entrada = sist_carregaArquivo();
    
    int **matriz = sist_leitura(entrada); // matriz principal com todos os sorteios
    
    // CORAÇÃO DO PROGRAMA | COLETA DE DADOS AO PERCORRER A MATRIZ 
    for(int i=0; i<LINHA; i++){ // percorre linhas
        for(int j=0; j<COLUNA; j++){ // percorre colunas
            if(EhPrimo(matriz[i][j])){ 
                vetorQtdPrimos[i]++; // conta numero de primos pra cada sorteio
            }
            
            vetorA[(matriz[i][j])-1]++; // armazena bolas do sorteio atual (booleano)
            if(i<LINHA-1){ // -1 para não "estourar" numero de sorteios        
                vetorB[(matriz[i+1][j])-1]++; // armazena bolas do sorteio posterior (booleano)  
            }

            qtdCadaNum[matriz[i][j]-1]++;
        }
        for(int k=0; k<NUM_BOLAS; k++){ 
            if(vetorA[k]==1 && vetorA[k+1]==1) // conta numeros em sequencia
                cont++;
            else { 
                if(cont > maior) 
                    maior = cont;
                cont = 1; // restaura
            }

            if(i<LINHA-1){ // -1 para não "estourar" numero de sorteios
                vetorC[k] = vetorA[k] + vetorB[k];
                if(vetorC[k] == 2){ // se é 2 a mesma bola foi sorteada nos sorteios "atual" e "posterior"
                    vetorQtdRepeteAnterior[i]++;
                }
                vetorA[k] = 0; // restaura
                vetorB[k] = 0; // restaura
            }
        }
        vetorQtdConsecutivos[i] = maior;
        maior = 0; // restaura
    }
    for(int i=0; i<LINHA; i++){
        vetorQtdNumConsec[vetorQtdConsecutivos[i]-1]++;
        vetorQtdNumPrimos[vetorQtdPrimos[i]]++;
        vetorQtdNumRepete[vetorQtdRepeteAnterior[i]-1]++;
    }

    // CALCULOS E RELATORIOS
    float mediaPrimos = calculaMedia(vetorQtdPrimos);
    float mediaConsecutivos = calculaMedia(vetorQtdConsecutivos);
    float mediaRepeteAnterior = calculaMedia(vetorQtdRepeteAnterior);

    int modaPrimos = calculaModa(vetorQtdPrimos);
    int modaRepetidos = calculaModa(vetorQtdRepeteAnterior);
    int modaConsecutivos = calculaModa(vetorQtdConsecutivos);

    float *percPrimos = calculaPercentual(vetorQtdNumPrimos);
    float *percConsecutivos = calculaPercentual(vetorQtdNumConsec);
    float *percRepete = calculaPercentual(vetorQtdNumRepete);

    sist_exibeRelatorios(mediaPrimos, mediaRepeteAnterior, mediaConsecutivos, modaPrimos, modaRepetidos, modaConsecutivos, percPrimos, percConsecutivos, percRepete);

    extra(qtdCadaNum);

    // LIBERA MEMÓRIA UTILIZADA
    free(percPrimos);
    free(percConsecutivos);
    free(percRepete);
    liberaMatriz(matriz);

    return 0;
}