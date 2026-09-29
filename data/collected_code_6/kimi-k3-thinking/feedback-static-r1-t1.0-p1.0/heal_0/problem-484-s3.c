#include <stdio.h>
#include <stdlib.h>

static int contains(const int *arr, size_t size, int value)
{
    size_t i;
    if (arr == NULL) {
        return 0;
    }
    for (i = 0; i < size; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

int remove_matching_tuples(const int *tuple1, size_t size1,
                           const int *tuple2, size_t size2,
                           int **result1, size_t *result_size1,
                           int **result2, size_t *result_size2)
{
    int *res1 = NULL;
    int *res2 = NULL;
    size_t count1 = 0;
    size_t count2 = 0;
    size_t i;

    if (result1 == NULL || result2 == NULL ||
        result_size1 == NULL || result_size2 == NULL) {
        return -1;
    }

    *result1 = NULL;
    *result2 = NULL;
    *result_size1 = 0;
    *result_size2 = 0;

    if ((size1 > 0 && tuple1 == NULL) || (size2 > 0 && tuple2 == NULL)) {
        return -1;
    }

    res1 = (int *)malloc((size1 > 0 ? size1 : 1) * sizeof(int));
    if (res1 == NULL) {
        return -1;
    }

    res2 = (int *)malloc((size2 > 0 ? size2 : 1) * sizeof(int));
    if (res2 == NULL) {
        free(res1);
        res1 = NULL;
        return -1;
    }

    for (i = 0; i < size1; i++) {
        if (!contains(tuple2, size2, tuple1[i])) {
            res1[count1] = tuple1[i];
            count1++;
        }
    }

    for (i = 0; i < size2; i++) {
        if (!contains(tuple1, size1, tuple2[i])) {
            res2[count2] = tuple2[i];
            count2++;
        }
    }

    *result1 = res1;
    *result2 = res2;
    *result_size1 = count1;
    *result_size2 = count2;

    return 0;
}

static void print_tuple(const char *label, const int *arr, size_t size)
{
    size_t i;
    printf("%s: (", label);
    for (i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i + 1 < size) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {4, 5, 6, 7, 8};
    int *result1 = NULL;
    int *result2 = NULL;
    size_t result_size1 = 0;
    size_t result_size2 = 0;

    if (remove_matching_tuples(tuple1, sizeof(tuple1) / sizeof(tuple1[0]),
                               tuple2, sizeof(tuple2) / sizeof(tuple2[0]),
                               &result1, &result_size1,
                               &result2, &result_size2) != 0) {
        fprintf(stderr, "Error: failed to remove matching tuples\n");
        free(result1);
        free(result2);
        return EXIT_FAILURE;
    }

    print_tuple("Tuple 1 after removal", result1, result_size1);
    print_tuple("Tuple 2 after removal", result2, result_size2);

    free(result1);
    result1 = NULL;
    free(result2);
    result2 = NULL;

    return EXIT_SUCCESS;
}