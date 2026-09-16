#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_pair(int a, int b)
{
    return (a == b) ? 1 : 0;
}

static int *map_lists(const int *list1, const int *list2, size_t n, int (*func)(int, int))
{
    size_t i;
    int *result;

    if (list1 == NULL || list2 == NULL || func == NULL || n == 0U) {
        return NULL;
    }

    result = malloc(n * sizeof *result);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < n; i++) {
        result[i] = func(list1[i], list2[i]);
    }

    return result;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 4, got <no output>
  */

static int count_same_pair(const int *list1, const int *list2, size_t n)
{
    size_t i;
    int count;
    int *mapped;

    if (n == 0U) {
        return 0;
    }

    mapped = map_lists(list1, list2, n, compare_pair);
    if (mapped == NULL) {
        return -1;
    }

    count = 0;
    for (i = 0U; i < n; i++) {
        count += mapped[i];
    }

    free(mapped);
    return count;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    /* Possible weaknesses found:
     *  Variable 'list2' can be declared as const array [constVariable]
     */
    int list2[] = {2, 2, 3, 1, 2, 6, 7, 9};
    size_t n = sizeof list1 / sizeof list1[0];
    int result;

    result = count_same_pair(list1, list2, n);
    if (result < 0) {
        (void)fprintf(stderr, "Error: failed to compute pair count\n");
        return EXIT_FAILURE;
    }

    if (printf("Number of same pairs: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}