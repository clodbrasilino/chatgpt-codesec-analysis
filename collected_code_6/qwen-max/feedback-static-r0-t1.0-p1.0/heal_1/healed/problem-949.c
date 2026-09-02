#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int a;
    int b;
} Tuple;

int countDigits(int number) {
    if (number == 0) return 1;
    number = abs(number);
    return (int)log10(number) + 1;
}

int totalDigits(Tuple t) {
    return countDigits(t.a) + countDigits(t.b);
}

int compare(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    return totalDigits(*tupleA) - totalDigits(*tupleB);
}

void printTuples(Tuple *tuples, int n) {
    for (int i = 0; i < n; ++i) {
        printf("(%d, %d) ", tuples[i].a, tuples[i].b);
    }
    printf("\n");
}

int main() {
    Tuple tuples[] = {{123, 45}, {67, 89}, {10, 2345}, {6, 789}};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    qsort(tuples, n, sizeof(Tuple), compare);
    printTuples(tuples, n);
    return 0;
}