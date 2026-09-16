#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

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

    if (n > SIZE_MAX / sizeof(*result)) {
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
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got <no output>
  *  test case 0 failed: expected 4, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

static int count_same_pair(const int *list1, const int *list2, size_t n)
{
    int *mapped;
    int count = 0;
    size_t i;

    if (n == 0U) {
        return 0;
    }

    if (list1 == NULL || list2 == NULL) {
        return -1;
    }

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

static int read_list(int *list, size_t n)
{
    size_t i;

    if (list == NULL) {
        return -1;
    }

    for (i = 0U; i < n; i++) {
        if (scanf("%d", &list[i]) != 1) {
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    size_t n;
    unsigned long input_n;
    int *list1;
    int *list2;
    int result;

    if (scanf("%lu", &input_n) != 1) {
        fprintf(stderr, "Error: failed to read size\n");
        return EXIT_FAILURE;
    }

    n = (size_t)input_n;

    if (n == 0U) {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    if (n > SIZE_MAX / sizeof(*list1)) {
        fprintf(stderr, "Error: size too large\n");
        return EXIT_FAILURE;
    }

    list1 = malloc(n * sizeof(*list1));
    if (list1 == NULL) {
        fprintf(stderr, "Error: allocation failed\n");
        return EXIT_FAILURE;
    }

    list2 = malloc(n * sizeof(*list2));
    if (list2 == NULL) {
        free(list1);
        fprintf(stderr, "Error: allocation failed\n");
        return EXIT_FAILURE;
    }

    if (read_list(list1, n) != 0 || read_list(list2, n) != 0) {
        free(list1);
        free(list2);
        fprintf(stderr, "Error: failed to read lists\n");
        return EXIT_FAILURE;
    }

    result = count_same_pair(list1, list2, n);
    free(list1);
    free(list2);

    if (result < 0) {
        fprintf(stderr, "Error: failed to count pairs\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}