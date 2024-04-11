#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    int a;
    int b;
} Tuple;

typedef struct TupleCount {
    Tuple tuple;
    int count;
} TupleCount;

int findTupleIndex(TupleCount* tupleCounts, int n, Tuple tuple) {
    for (int i = 0; i < n; i++) {
        if (tupleCounts[i].tuple.a == tuple.a && tupleCounts[i].tuple.b == tuple.b) {
            return i;
        }
    }
    return -1;
}

void countTupleFrequencies(Tuple* tuples, int n) {
    TupleCount* tupleCounts = (TupleCount*)malloc(n * sizeof(TupleCount));
    
    if (tupleCounts == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        int index = findTupleIndex(tupleCounts, count, tuples[i]);
        if (index != -1) {
            tupleCounts[index].count++;
        } else {
            tupleCounts[count].tuple = tuples[i];
            tupleCounts[count].count = 1;
            count++;
        }
    }

    for (int i = 0; i < count; i++) {
        printf("(%d, %d): %d\n", tupleCounts[i].tuple.a, tupleCounts[i].tuple.b, tupleCounts[i].count);
    }

    free(tupleCounts);
}

int main() {
    Tuple tuples[] = {{1, 2}, {2, 3}, {1, 2}, {4, 5}, {2, 3}, {1, 2}};
    int n = sizeof(tuples) / sizeof(Tuple);

    countTupleFrequencies(tuples, n);

    return 0;
}