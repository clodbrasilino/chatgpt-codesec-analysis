#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *arr, size_t len, int value)
{
    if (arr == NULL) {
        return false;
    }
    for (size_t i = 0; i < len; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected [34, 36, 11, 25], got <no output>
  *  test case 1 failed: expected [1, 4, 7, 9], got <no output>
  *  test case 0 failed: expected [3, 6, 7, 10], got <no output>
  */

static int *find_dissimilar(const int *tup1, size_t len1,
                            const int *tup2, size_t len2,
                            size_t *result_len)
{
    if (result_len == NULL) {
        return NULL;
    }

    *result_len = 0;

    if (tup1 == NULL || tup2 == NULL) {
        return NULL;
    }

    size_t max_len = len1 + len2;
    if (max_len < len1 || max_len == 0) {
        return NULL;
    }

    int *result = malloc(max_len * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;

    for (size_t i = 0; i < len1; i++) {
        if (!contains(tup2, len2, tup1[i]) && !contains(result, count, tup1[i])) {
            result[count++] = tup1[i];
        }
    }

    for (size_t i = 0; i < len2; i++) {
        if (!contains(tup1, len1, tup2[i]) && !contains(result, count, tup2[i])) {
            result[count++] = tup2[i];
        }
    }

    *result_len = count;
    return result;
}

static void print_result(const int *result, size_t result_len)
{
    printf("[");
    if (result != NULL) {
        for (size_t i = 0; i < result_len; i++) {
            if (i > 0) {
                printf(", ");
            }
            printf("%d", result[i]);
        }
    }
    printf("]\n");
    fflush(stdout);
}

static int run_case(const int *tup1, size_t len1, const int *tup2, size_t len2)
{
    size_t result_len = 0;
    int *result = find_dissimilar(tup1, len1, tup2, len2, &result_len);

    if (result == NULL && (len1 + len2) > 0) {
        fprintf(stderr, "Failed to compute dissimilar elements\n");
        return -1;
    }

    print_result(result, result_len);
    free(result);
    return 0;
}

int main(void)
{
    int tuple1a[] = {3, 4, 5, 6};
    int tuple2a[] = {5, 7, 4, 10};

    int tuple1b[] = {1, 2, 3, 4};
    int tuple2b[] = {7, 2, 3, 9};

    int tuple1c[] = {34, 21, 36, 26};
    int tuple2c[] = {26, 11, 21, 25};

    if (run_case(tuple1a, sizeof(tuple1a) / sizeof(tuple1a[0]),
                 tuple2a, sizeof(tuple2a) / sizeof(tuple2a[0])) != 0) {
        return EXIT_FAILURE;
    }

    if (run_case(tuple1b, sizeof(tuple1b) / sizeof(tuple1b[0]),
                 tuple2b, sizeof(tuple2b) / sizeof(tuple2b[0])) != 0) {
        return EXIT_FAILURE;
    }

    if (run_case(tuple1c, sizeof(tuple1c) / sizeof(tuple1c[0]),
                 tuple2c, sizeof(tuple2c) / sizeof(tuple2c[0])) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}