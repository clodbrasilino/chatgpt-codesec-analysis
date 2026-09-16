#include <stdio.h>
#include <stdlib.h>

double find_average(int **tuples, int tuple_count, const int *tuple_sizes) {
    if (tuple_count <= 0 || tuple_sizes == NULL || tuples == NULL) {
        return 0.0;
    }

    long long total_sum = 0;
    int total_count = 0;

    for (int i = 0; i < tuple_count; i++) {
        if (tuples[i] == NULL) {
            continue;
        }
        for (int j = 0; j < tuple_sizes[i]; j++) {
            total_sum += tuples[i][j];
            total_count++;
        }
    }

    if (total_count == 0) {
        return 0.0;
    }

    return (double)total_sum / total_count;
}

int main(void) {
    int row1[] = {1, 2, 3};
    int row2[] = {4, 5, 6, 7};
    int row3[] = {8, 9};

    int *tuples[] = {row1, row2, row3};
    int tuple_sizes[] = {3, 4, 2};
    int tuple_count = 3;

    double avg = find_average(tuples, tuple_count, tuple_sizes);
    printf("%f\n", avg);

    return 0;
}