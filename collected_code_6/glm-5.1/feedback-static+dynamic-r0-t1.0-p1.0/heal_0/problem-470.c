#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int* pairwise_addition(Tuple* tuples, size_t count, size_t* result_count) {
    if (tuples == NULL || result_count == NULL || count == 0) {
        return NULL;
    }

    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; ++i) {
        result[i] = tuples[i].a + tuples[i].b;
    }

    *result_count = count;
    return result;
}

int main(void) {
    Tuple data[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    size_t count = sizeof(data) / sizeof(data[0]);
    size_t result_count = 0;

    int* sums = pairwise_addition(data, count, &result_count);

    if (sums != NULL) {
        for (size_t i = 0; i < result_count; ++i) {
            printf("%d ", sums[i]);
        }
        printf("\n");
        free(sums);
        sums = NULL;
    } else {
        fprintf(stderr, "Allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}