#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    int size;
} Tuple;

int max_column_n(Tuple *tuples, int tuple_count, int column) {
    int max = tuples[0].values[column];
    for (int i = 1; i < tuple_count; i++) {
        if (tuples[i].values[column] > max) {
            max = tuples[i].values[column];
        }
    }
    return max;
}

int main(void) {
    int values1[] = {1, 2, 3};
    int values2[] = {4, 5, 6};
    int values3[] = {7, 8, 9};

    Tuple tuples[] = {
        {values1, 3},
        {values2, 3},
        {values3, 3}
    };

    int result = max_column_n(tuples, 3, 1);
    printf("%d\n", result);

    return 0;
}