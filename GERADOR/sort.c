#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

#define TAM 15

void insert_sort(int *a){
    int lo = 0, hi = TAM;
    int min;
    for (int i=lo; i<hi; i++){
        min = i;
        for (int j=i+1; j<hi; j++)
            if (less(key(a[j]),key(a[min]))) min=j;
        exch(key(a[i]),key(a[min]));
    }
}