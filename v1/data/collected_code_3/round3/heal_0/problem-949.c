#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int countDigits(int n) {
    int count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }
    return count;
}

int compare(const void* a, const void* b) {
    Tuple* tupleA = (Tuple*)a;
    Tuple* tupleB = (Tuple*)b;

    int sumA = countDigits(tupleA->a) + countDigits(tupleA->b);
    int sumB = countDigits(tupleB->a) + countDigits(tupleB->b);

    return sumA - sumB;
}

void sortTuples(Tuple* tuples, int n) {
    qsort(tuples, n, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{123, 45}, {12, 345}, {1234, 5}, {1, 2345}};
    int n = sizeof(tuples) / sizeof(tuples[0]);

    sortTuples(tuples, n);

    for (int i = 0; i < n; i++) {
        printf("(%d, %d)\n", tuples[i].a, tuples[i].b);
    }

    return 0;
}