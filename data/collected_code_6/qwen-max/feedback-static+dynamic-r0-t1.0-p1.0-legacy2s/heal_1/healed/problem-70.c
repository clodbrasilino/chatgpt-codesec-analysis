#include <stdio.h>
#include <stdlib.h>

int allTuplesEqualLength(int ***tuples, int n, const int *m) {
    for (int i = 1; i < n; i++) {
        if (m[i] != m[0]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n = 4;
    int **tuples = (int **)malloc(n * sizeof(int *));
    const int lengths[] = {3, 3, 3, 3};

    for (int i = 0; i < n; i++) {
        tuples[i] = (int *)malloc(lengths[0] * sizeof(int));
        for (int j = 0; j < lengths[0]; j++) {
            tuples[i][j] = j + 1;
        }
    }

    int result = allTuplesEqualLength(&tuples, n, lengths);
    printf("All tuples have equal length: %s\n", result ? "True" : "False");

    for (int i = 0; i < n; i++) {
        free(tuples[i]);
    }
    free(tuples);

    return 0;
}