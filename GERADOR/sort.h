#ifndef SORT_H
#define SORT_H

#define key(A)          (A)
#define less(A, B)      (key(A) < key(B)) //verifica se é menor
#define exch(A, B)      { int t = A; A = B; B = t; } //faz a troca de posições
#define compexch(A, B)  if (less(B, A)) exch(A, B) //algoritmo = verifica + troca
#define compexchr(A, B) if (!less(B, A)) exch(A, B) //algoritmo inverso (reversed)

void insert_sort(int *a);

#endif /* SORT_H */