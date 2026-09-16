#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    int arity;
} Tuple;

int find_max_column(Tuple *tuples, int num_tuples, int n) {
    if (tuples == NULL || num_tuples <= 0 || n < 0) {
        exit(EXIT_FAILURE);
    }

    if (tuples[0].arity <= n) {
        exit(EXIT_FAILURE);
    }

    int max_val = tuples[0].values[n];

    for (int i = 1; i < num_tuples; i++) {
        if (tuples[i].values == NULL) {
            exit(EXIT_FAILURE);
        }
        if (tuples[i].arity <= n) {
            exit(EXIT_FAILURE);
        }
        if (tuples[i].values[n] > max_val) {
            max_val = tuples[i].values[n];
        }
    }

    return max_val;
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    int data3[] = {7, 0, 8};

    Tuple tuples[] = {
        {data1, 3},
        {data2, 3},
        {data3, 3}
    };

    int result = find_max_column(tuples, 3, 1);
    printf("%d\n", result);

    return 0;
}