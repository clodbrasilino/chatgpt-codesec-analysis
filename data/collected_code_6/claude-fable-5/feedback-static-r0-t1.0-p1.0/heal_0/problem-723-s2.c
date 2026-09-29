#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef int (*pair_func)(int, int);

static int is_equal(int a, int b)
{
    return (a == b) ? 1 : 0;
}

static int *map_pairs(const int *list1, const int *list2, size_t n, pair_func f)
{
    int *result;
    size_t i;

    if (list1 == NULL || list2 == NULL || f == NULL || n == 0U) {
        return NULL;
    }

    result = malloc(n * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < n; i++) {
        result[i] = f(list1[i], list2[i]);
    }

    return result;
}

static int count_same_pair(const int *list1, const int *list2, size_t n)
{
    int *mapped;
    int count = 0;
    size_t i;

    mapped = map_pairs(list1, list2, n, is_equal);
    if (mapped == NULL) {
        return -1;
    }

    for (i = 0U; i < n; i++) {
        count += mapped[i];
    }

    free(mapped);
    return count;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int list2[] = {1, 2, 4, 4, 5, 7, 7, 9};
    size_t n = sizeof(list1) / sizeof(list1[0]);
    int result;

    result = count_same_pair(list1, list2, n);
    if (result < 0) {
        if (fprintf(stderr, "Error: failed to count pairs\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Number of same pairs: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}