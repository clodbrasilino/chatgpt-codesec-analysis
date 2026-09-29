#include <stdio.h>
#include <stdlib.h>

int all_tuples_equal_length(int **tuples, int n, const int *lengths) {
    if (n <= 0) return 1;
    for (int i = 1; i < n; ++i) {
        if (lengths[i] != lengths[0]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n = 5;
    int lengths[] = {3, 3, 3, 3, 3};
    int **tuples = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        tuples[i] = (int *)malloc(lengths[i] * sizeof(int));
    }

    if (all_tuples_equal_length(tuples, n, lengths)) {
        printf("All tuples have equal length.\n");
    } else {
        printf("Not all tuples have equal length.\n");
    }

    for (int i = 0; i < n; ++i) {
        free(tuples[i]);
    }
    free(tuples);

    return 0;
}