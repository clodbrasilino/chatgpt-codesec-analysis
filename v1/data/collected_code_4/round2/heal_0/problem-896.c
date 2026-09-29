#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} tuple;

int compare(const void *a, const void *b) {
    const tuple *tupleA = a;
    const tuple *tupleB = b;

    if(tupleA->b > tupleB->b)
        return 1;
    else if(tupleA->b < tupleB->b)
        return -1;
    else
        return 0;
}

void sortTuples(tuple *tuples, int tupleCount) {
    if(tuples != NULL && tupleCount > 0) {
        qsort(tuples, tupleCount, sizeof(tuple), compare);
    }
}

int main(void) {
    tuple tuples[] = {{1, 2}, {3, 1}, {2, 3}, {4, 2}};
    int tupleCount = sizeof(tuples)/sizeof(tuple);
    
    sortTuples(tuples, tupleCount);
    
    for(int i = 0; i < tupleCount; i++) {
        printf("{%d, %d} ", tuples[i].a, tuples[i].b);
    }
    
    return 0;
}