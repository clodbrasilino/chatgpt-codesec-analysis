#include <stdio.h>
#include <stdlib.h>

void pairwise_addition(int *tuple1, int *tuple2, int *result, int size) {
    for (int i = 0; i < size; ++i) {
        result[i] = tuple1[i] + tuple2[i];
    }
}

int main() {
    int size;
    printf("Enter the size of the tuples: ");
    scanf("%d", &size);

    int *tuple1 = (int *)malloc(size * sizeof(int));
    int *tuple2 = (int *)malloc(size * sizeof(int));
    int *result = (int *)malloc(size * sizeof(int));

    if (tuple1 == NULL || tuple2 == NULL || result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    printf("Enter elements of the first tuple:\n");
    for (int i = 0; i < size; ++i) {
        scanf("%d", &tuple1[i]);
    }

    printf("Enter elements of the second tuple:\n");
    for (int i = 0; i < size; ++i) {
        scanf("%d", &tuple2[i]);
    }

    pairwise_addition(tuple1, tuple2, result, size);

    printf("Result of pairwise addition:\n");
    for (int i = 0; i < size; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(tuple1);
    free(tuple2);
    free(result);

    return 0;
}