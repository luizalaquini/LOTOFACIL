#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include "sort.h"

#define NUM_BOLAS 25
#define TAM 15 // tamanho do sorteio 

int main(void) {

    sist_introducao();

    /* DECLARA VARIÁVEIS NECESSÁRIAS */
    int *anterior = sist_pedeAnterior();
    int *numeros = (int*) malloc (TAM * sizeof(int));

    /* SORTEIO DE NÚMEROS DE ACORDO COM AS REGRAS */
    do {
        geraNumeros(numeros);
        insert_sort(numeros); // ordena em ordem crescente
    } while (!obedeceRegras(numeros, anterior));

    /* IMPRIME RESULTADO */
    resultado(numeros);
    
    // Liberando memória utilizada 
    free(numeros);
    free(anterior);

    return 0;
}