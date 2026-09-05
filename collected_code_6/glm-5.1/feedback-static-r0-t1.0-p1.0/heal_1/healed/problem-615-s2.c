#include <stdio.h>
#include <stdlib.h>

double find_average(int * const *tuples, int num_tuples, const int *tuple_sizes) {
    if (tuples == NULL || num_tuples <= 0 || tuple_sizes == NULL) {
        return 0.0;
    }

    long long total_sum = 0;
    int total_count = 0;

    for (int i = 0; i < num_tuples; i++) {
        if (tuples[i] == NULL || tuple_sizes[i] < 0) {
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
    const int sizes[] = {3, 4, 2};
    const int tuple1[] = {1, 2, 3};
    const int tuple2[] = {4, 5, 6, 7};
    const int tuple3[] = {8, 9};

    const int * const tuples[] = {tuple1, tuple2, tuple3};
    
    double avg = find_average(tuples, 3, sizes);
    
    printf("%f\n", avg);
    
    return 0;
}