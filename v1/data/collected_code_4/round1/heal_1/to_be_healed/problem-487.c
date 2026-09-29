#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int comparison(const void *p, const void *q) {
    Tuple *tuple1 = (Tuple *)p;
    Tuple *tuple2 = (Tuple *)q;

    if(tuple1->b < tuple2->b) {
        return -1;
    }
    if(tuple1->b > tuple2->b) {
        return 1;
    }
    return 0;
}

void sortTuples(Tuple *tuples, int tupleCount) {
    qsort((void*)tuples, tupleCount, sizeof(Tuple), comparison);
}

int main() {
    int size = 5;
    Tuple *tuples = (Tuple*)malloc(sizeof(Tuple) * size);
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'tuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    tuples[0].a = 1;
    tuples[0].b = 4;
    tuples[1].a = 2;
    tuples[1].b = 3;
    tuples[2].a = 3;
    tuples[2].b = 5;
    tuples[3].a = 4;
    tuples[3].b = 1;
    tuples[4].a = 5;
    tuples[4].b = 2;

    sortTuples(tuples, size);

    for (int i = 0; i < size; i++) {
         printf("Tuple: (%d, %d)\n", tuples[i].a, tuples[i].b);
    }
  
    free(tuples);
    return 0;
}