#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> // necessário p/ as funções rand() e srand()
#include <time.h> // necessário p/ função time()
#include "sistema.h"

#define NUM_BOLAS 25
#define TAM 15 // tamanho do sorteio 

/* DECLARAÇÃO DE FUNÇÕES AUXILIARES */
int EhPrimo (int num);
int EhImpar (int num);
int EhMetadeMenor (int num);
int troca (void);
/**/

void sist_introducao (void){
    printf("--------------------------------------------------------------------------\n");
    printf("---------------------- GERADOR DE JOGO DA LOTOFACIL ----------------------\n");
    printf("-------------------------- By: Luiza B. Laquini --------------------------\n\n");
}

int* sist_pedeAnterior (void){
    int* anterior = (int*) malloc (TAM * sizeof(int));

    printf("Digite o último jogo sorteado pela LOTOFÁCIL (separe os números apenas por espaços): ");

    for (int i=0; i<TAM; i++){
        scanf(" %d", &anterior[i]);
    }
    printf("\n");

    return anterior;
}

void geraNumeros (int *numeros){
    printf("- Gerando números...\n");

    srand(time(NULL));
    
    /*Para a função rand funcionar ela precisa de um valor inicial chamado de “semente”. 
    Se nenhum valor é passado rand assume um valor constante. No caso a função assume 1. 
    Como este valor, ou seja 1, é assumido sempre no programa acima, a sequência gerada 
    será a mesma para cada execução. */
    /* Sendo assim, srand(time(NULL)) objetiva inicializar o gerador de números aleatórios 
    com o valor da função time(NULL). Este por sua vez, é calculado como sendo o total de 
    segundos passados desde 1 de janeiro de 1970 até a data atual.Dessa forma, a cada execução 
    o valor da "semente" será diferente!
    */
    for (int i=0; i < TAM; i++){
        numeros[i] = (rand() % NUM_BOLAS)+1; // gerando valores aleatórios na faixa de 1 a 25
    } 
    
    // Até aqui pode ser que existam numeros repetidos na sequencia
    // Vamos retirar as repetições

    int aux[NUM_BOLAS]; // vetor auxiliar

    for (int i=0; i < NUM_BOLAS; i++) aux[i] = 0; // zerando
    
    int i =0;
    while (i<TAM){
        if (aux[numeros[i]-1] == 0){
            aux[numeros[i]-1]++;
            i++;
        }
        else { // aux[numeros[i]] > 0 
            numeros[i] = troca();
        }
    } 
}

int obedeceRegras (int *jogo, int *anterior){
    int primos = 0, repetidos = 0, consecutivos = 1, impares = 0, metadeMenor = 0;
    int maior = 0; // auxiliar

    for (int i=0; i<TAM; i++){
        if (EhPrimo(jogo[i])) // PRIMOS
            primos++;   
        if (EhImpar(jogo[i]))
            impares++; 
        if (EhMetadeMenor(jogo[i]))
            metadeMenor++;
        if(i < 14){ // CONSECUTIVOS
            if ((jogo[i]+1) == jogo[i+1]){
                consecutivos++;
            } else {
                if (consecutivos > maior) maior = consecutivos;
                consecutivos = 1; // reset
            }
        }
        for (int j=0; j<TAM; j++){ // REPETIDOS
            if(jogo[i] == anterior[j]) repetidos++;
        }
    }

    /*------------------- SUGESTÕES DE LIMITAÇÃO -------------------
    * PARA TODOS:
    * 6 a 9 números ímpares
    * 6 a 9 números menores que 14
    * */

    /*LIMITE AMPLO (Raphael):
    * 4 a 7 números primos
    * 7 a 11 números repetidos em relação ao sorteio anterior
    * Até 6 números consecutivos (maior sequencia de consecutivos)
    * */

    /*LIMITE MÉDIO (Luiza):
    * 5 ou 6 números primos
    * 8 a 10 números repetidos em relação ao sorteio anterior
    * 4 ou 5 números consecutivos (maior sequencia de consecutivos)
    * */

    /*LIMITE RESTRITÃO - só na moda
    * 5 números primos
    * 9 números repetidos em relação ao sorteio anterior
    * 4 ou 5 números consecutivos (maior sequencia de consecutivos)
    * */

    // A seguir, descomente apenas 1 if
    /*if (primos >= 4 && primos <= 7 && repetidos >= 7 && repetidos <= 11 && maior <=6 && impares >= 6 && impares <= 9 && metadeMenor >= 6 && metadeMenor){ // Limite amplo */
    if (primos >= 5 && primos <= 6 && repetidos >= 8 && repetidos <= 10 && maior >= 4 && maior <=5 && impares >= 6 && impares <= 9 && metadeMenor >= 6 && metadeMenor){ // Limite médio
    /* if (primos == 5 && repetidos == 9 && maior >= 4 && maior <=5 && impares >= 6 && impares <= 9 && metadeMenor >= 6 && metadeMenor){ // Limite restritão */
    
        printf("\nESSE JOGO CONTÉM:\n");
        printf("%d números pares + %d números ímpares\n", (TAM-impares), impares);
        printf("%d números menores < 14 (metade menor) + %d números >= 14 (metade maior)\n", metadeMenor, (TAM-metadeMenor));
        printf("%d números primos\n", primos);
        printf("%d números repetidos em relação ao sorteio anterior\n", repetidos);
        printf("Maior sequência de consecutivos de %d números\n\n", maior);

        return 1; 
    } 
    else return 0; // não obedece
}

int resultado (int* jogo){
    printf("Números:");
    for(int i=0; i<TAM; i++){
        printf(" %d", jogo[i]);
    }
    printf("\n");
}

/* FUNÇÕES AUXILIARES */

int troca (void){
    srand(time(NULL));
    return (rand() % NUM_BOLAS)+1;
}

int EhPrimo (int num){
    if (num == 2 || num == 3 || num == 5 || num == 7 || num == 11 || num == 13 || num == 17 || num == 19 || num == 23) return 1;
    else return 0;
}

int EhImpar (int num){
    if ((num % 2) > 0) return 1;
    else return 0;
}

int EhMetadeMenor (int num){
    if(num < 14) return 1;
    else return 0;
}