#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int maximize_tuples(const Pair *a, const Pair *b, Pair *result, size_t count)
{
    size_t i;

    if (a == NULL || b == NULL || result == NULL || count == 0U) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        result[i].first = (a[i].first > b[i].first) ? a[i].first : b[i].first;
        result[i].second = (a[i].second > b[i].second) ? a[i].second : b[i].second;
    }

    return 0;
}

int main(void)
{
    Pair tuple1[] = { {1, 3}, {4, 5}, {2, 9}, {1, 10} };
    Pair tuple2[] = { {6, 7}, {3, 9}, {1, 1}, {7, 3} };
    size_t count = sizeof(tuple1) / sizeof(tuple1[0]);
    Pair *result;
    size_t i;
    int status;

    result = (Pair *)malloc(count * sizeof(Pair));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = maximize_tuples(tuple1, tuple2, result, count);
    if (status != 0) {
        fprintf(stderr, "Failed to maximize tuples\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("Maximized tuples: ");
    for (i = 0U; i < count; i++) {
        printf("(%d, %d) ", result[i].first, result[i].second);
    }
    printf("\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}