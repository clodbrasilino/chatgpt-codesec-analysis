#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

void multiplyTuples(const int *tuple1, const int *tuple2, int64_t *result, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        int64_t prod = (int64_t)tuple1[i] * (int64_t)tuple2[i];
        if (prod > INT_MAX || prod < INT_MIN) {
            fprintf(stderr, "Integer overflow detected\n");
            exit(EXIT_FAILURE);
        }
        result[i] = (int)prod;
    }
}

int main() {
    size_t length;
    printf("Enter the length of the tuples: ");
    if (scanf("%zu", &length) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int *tuple1 = malloc(length * sizeof(int));
    int *tuple2 = malloc(length * sizeof(int));
    int64_t *result = malloc(length * sizeof(int64_t));

    if (tuple1 == NULL || tuple2 == NULL || result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(tuple1);
        free(tuple2);
        free(result);
        return EXIT_FAILURE;
    }

    printf("Enter elements of first tuple:\n");
    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &tuple1[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(tuple1);
            free(tuple2);
            free(result);
            return EXIT_FAILURE;
        }
    }

    printf("Enter elements of second tuple:\n");
    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &tuple2[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(tuple1);
            free(tuple2);
            free(result);
            return EXIT_FAILURE;
        }
    }

    multiplyTuples(tuple1, tuple2, result, length);

    printf("Resultant tuple:\n");
    for (size_t i = 0; i < length; ++i) {
        printf("%lld ", (long long)result[i]);
    }
    printf("\n");

    free(tuple1);
    free(tuple2);
    free(result);
    return EXIT_SUCCESS;
}