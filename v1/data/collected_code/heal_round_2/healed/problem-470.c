#include <stdio.h>
#include <stdlib.h>

void pairwiseAddition(const int tuple1[], const int tuple2[], int length) {
    int *result = (int *)malloc(sizeof(int) * length);
    if (result == NULL) {
        printf("Memory allocation failed for result array");
        return;
    }

    for (int i = 0; i < length; i++) {
        result[i] = tuple1[i] + tuple2[i];
    }

    printf("Pairwise Addition: (");
    for (int i = 0; i < length - 1; i++) {
        printf("%d, ", result[i]);
    }

    printf("%d)\n", result[length - 1]);

    free(result);
}

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {4, 5, 6};
    int length = sizeof(tuple1) / sizeof(tuple1[0]);

    pairwiseAddition(tuple1, tuple2, length);

    return 0;
}