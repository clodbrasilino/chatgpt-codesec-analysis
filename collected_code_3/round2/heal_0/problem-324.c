#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

int sumAlternateChains(Tuple* tuples, int size) {
    int sum = 0;
    for(int i = 0; i < size; i += 2) {
        sum += tuples[i].a + tuples[i].b;
    }
    return sum;
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    int size = sizeof(tuples) / sizeof(Tuple);
    int sum = sumAlternateChains(tuples, size);
    printf("Sum of alternate chains of tuples: %d\n", sum);
    return 0;
}