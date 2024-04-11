#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
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

    int countA = countDigits(tupleA->first) + countDigits(tupleA->second);
    int countB = countDigits(tupleB->first) + countDigits(tupleB->second);

    return countA - countB;
}

void sortTuples(Tuple* tuples, int size) {
    qsort(tuples, size, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{123, 45}, {6, 789}, {10, 111}, {222, 333}};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    sortTuples(tuples, size);

    for (int i = 0; i < size; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }

    return 0;
}