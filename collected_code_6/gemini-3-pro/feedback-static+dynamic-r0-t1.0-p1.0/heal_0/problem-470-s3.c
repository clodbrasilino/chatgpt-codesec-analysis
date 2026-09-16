#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

Tuple* pairwise_addition(const Tuple* tuples1, const Tuple* tuples2, size_t length) {
    if (tuples1 == NULL || tuples2 == NULL || length == 0) {
        return NULL;
    }

    Tuple* result = (Tuple*)malloc(length * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        result[i].x = tuples1[i].x + tuples2[i].x;
        result[i].y = tuples1[i].y + tuples2[i].y;
    }

    return result;
}

int main(void) {
    size_t length = 3;
    Tuple tuples1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple tuples2[] = {{7, 8}, {9, 10}, {11, 12}};

    Tuple* result = pairwise_addition(tuples1, tuples2, length);

    if (result != NULL) {
        for (size_t i = 0; i < length; ++i) {
            printf("(%d, %d)\n", result[i].x, result[i].y);
        }
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}