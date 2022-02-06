#ifndef SISTEMA_H
#define SISTEMA_H

/* INTRODUÇÃO ESCRITA DO PROGRAMA*/
void sist_introducao (void);

/* PEDE PARA O USUÁRIO ENTRAR COM O ÚLTIMO SORTEIO DA LOTOFÁCIL*/
int* sist_pedeAnterior (void);

/* GERA 15 NÚMEROS ALEATÓRIOS DE 1 A 25 - Problema: Números podem se repetir aqui*/
void geraNumeros (int* numeros);

/* RETORNA VERDADEIRO CASO O JOGO OBEDEÇA AS REGRAS DE ESTATÍSTICA DEFINIDAS*/
int obedeceRegras (int* jogo, int* anterior);

/* IMPRIME JOGO PARA SER JOGADO */
int resultado (int* jogo);

#endif /* SISTEMA_H */ 