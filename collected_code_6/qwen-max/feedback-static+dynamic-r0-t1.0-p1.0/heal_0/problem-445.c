#include <stdio.h>
#include <stdlib.h>

void multiply_tuples(const int *tuple1, const int *tuple2, int *result, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        result[i] = tuple1[i] * tuple2[i];
    }
}

int main() {
    size_t length;
    printf("Enter the length of the tuples: ");
    scanf("%zu", &length);

    int *tuple1 = malloc(length * sizeof(int));
    int *tuple2 = malloc(length * sizeof(int));
    int *result = malloc(length * sizeof(int));

    if (tuple1 == NULL || tuple2 == NULL || result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter elements of the first tuple:\n");
    for (size_t i = 0; i < length; ++i) {
        scanf("%d", &tuple1[i]);
    }

    printf("Enter elements of the second tuple:\n");
    for (size_t i = 0; i < length; ++i) {
        scanf("%d", &tuple2[i]);
    }

    multiply_tuples(tuple1, tuple2, result, length);

    printf("Resultant tuple after multiplication:\n");
    for (size_t i = 0; i < length; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(tuple1);
    free(tuple2);
    free(result);

    return 0;
}