#include <stdio.h>
#include <stdlib.h>

double find_average(int **tuples, int tuple_count, const int *tuple_sizes) {
    if (tuples == NULL || tuple_sizes == NULL || tuple_count <= 0) {
        return 0.0;
    }

    long long total_sum = 0;
    int total_count = 0;

    for (int i = 0; i < tuple_count; i++) {
        if (tuples[i] == NULL && tuple_sizes[i] > 0) {
            return 0.0;
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
    int row2[] = {4, 5, 6};
    int row3[] = {7, 8, 9, 10};
    
    int *tuples[] = {row1, row2, row3};
    /* Possible weaknesses found:
     *  Variable 'tuple_sizes' can be declared as const array [constVariable]
     */
    int tuple_sizes[] = {3, 3, 4};
    
    double avg = find_average(tuples, 3, tuple_sizes);
    printf("%f\n", avg);
    
    return 0;
}