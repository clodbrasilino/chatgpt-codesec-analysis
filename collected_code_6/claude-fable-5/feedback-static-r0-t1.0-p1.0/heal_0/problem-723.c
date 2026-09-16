#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef int (*pair_func)(int, int);

static int is_equal(int a, int b)
{
    return (a == b) ? 1 : 0;
}

static int *map2(const int *list1, const int *list2, size_t n, pair_func f)
{
    int *result;
    size_t i;

    if (list1 == NULL || list2 == NULL || f == NULL || n == 0U) {
        return NULL;
    }

    result = malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < n; i++) {
        result[i] = f(list1[i], list2[i]);
    }

    return result;
}

static int count_same_pair(const int *list1, const int *list2, size_t n, int *count)
{
    int *mapped;
    size_t i;
    int total;

    if (count == NULL) {
        return -1;
    }

    *count = 0;

    mapped = map2(list1, list2, n, is_equal);
    if (mapped == NULL) {
        return -1;
    }

    total = 0;
    for (i = 0U; i < n; i++) {
        total += mapped[i];
    }

    free(mapped);
    mapped = NULL;

    *count = total;
    return 0;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int list2[] = {1, 2, 3, 9, 5, 0, 7, 8};
    size_t n = sizeof(list1) / sizeof(list1[0]);
    int count = 0;

    if (count_same_pair(list1, list2, n, &count) != 0) {
        if (fprintf(stderr, "Error: failed to count pairs\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Number of same pairs: %d\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}