#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
} Tuple;

int isDivisibleByK(int num, int k) {
    return num % k == 0;
}

int isTupleDivisibleByK(Tuple t, int k) {
    for (int i = 0; i < t.size; ++i) {
        if (!isDivisibleByK(t.arr[i], k)) {
            return 0;
        }
    }
    return 1;
}

void freeTuple(Tuple t) {
    free(t.arr);
}

int main() {
    Tuple tuples[] = {
        {malloc(3 * sizeof(int)), 3},
        {malloc(4 * sizeof(int)), 4},
        {malloc(5 * sizeof(int)), 5},
        {malloc(5 * sizeof(int)), 5}
    };

    tuples[0].arr[0] = 3;
    tuples[0].arr[1] = 6;
    tuples[0].arr[2] = 9;

    tuples[1].arr[0] = 2;
    tuples[1].arr[1] = 4;
    tuples[1].arr[2] = 8;
    tuples[1].arr[3] = 16;

    tuples[2].arr[0] = 5;
    tuples[2].arr[1] = 10;
    tuples[2].arr[2] = 15;
    tuples[2].arr[3] = 20;
    tuples[2].arr[4] = 25;

    tuples[3].arr[0] = 1;
    tuples[3].arr[1] = 2;
    tuples[3].arr[2] = 3;
    tuples[3].arr[3] = 4;
    tuples[3].arr[4] = 5;

    int n = sizeof(tuples) / sizeof(tuples[0]);
    int k = 5;

    for (int i = 0; i < n; ++i) {
        if (isTupleDivisibleByK(tuples[i], k)) {
            for (int j = 0; j < tuples[i].size; ++j) {
                printf("%d ", tuples[i].arr[j]);
            }
            printf("\n");
        }
        freeTuple(tuples[i]);
    }

    return 0;
}