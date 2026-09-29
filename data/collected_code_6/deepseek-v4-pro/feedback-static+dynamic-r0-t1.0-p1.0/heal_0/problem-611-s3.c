#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

int maximum_of_nth_column(Tuple *tuples, int tuple_count, int column) {
    if (tuples == NULL || tuple_count <= 0 || column < 0) {
        fprintf(stderr, "Invalid input parameters\n");
        exit(EXIT_FAILURE);
    }

    int max = tuples[0].data[column];
    for (int i = 1; i < tuple_count; i++) {
        if (tuples[i].data[column] > max) {
            max = tuples[i].data[column];
        }
    }
    return max;
}

int main(void) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    int data3[] = {7, 8, 9};

    Tuple tuples[3];
    tuples[0].data = data1;
    tuples[0].size = 3;
    tuples[1].data = data2;
    tuples[1].size = 3;
    tuples[2].data = data3;
    tuples[2].size = 3;

    int column = 1;
    int result = maximum_of_nth_column(tuples, 3, column);
    printf("Maximum of column %d: %d\n", column, result);

    return 0;
}