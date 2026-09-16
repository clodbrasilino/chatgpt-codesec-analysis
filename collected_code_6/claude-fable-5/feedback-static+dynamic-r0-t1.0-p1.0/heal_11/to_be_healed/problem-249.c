#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static bool contains(const int *arr, size_t len, int value)
{
    for (size_t i = 0; i < len; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected [3, 5, 7, 9], got <no output>
  *  test case 0 failed: expected [1, 2, 8, 9], got <no output>
  *  test case 2 failed: expected [10], got <no output>
  */

int *intersection(const int *arr1, size_t len1,
                  const int *arr2, size_t len2,
                  size_t *result_len)
{
    if (result_len == NULL) {
        return NULL;
    }

    *result_len = 0;

    if (arr1 == NULL || arr2 == NULL || len1 == 0 || len2 == 0) {
        return NULL;
    }

    size_t cap = (len1 < len2) ? len1 : len2;

    int *result = malloc(cap * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < len1; i++) {
        if (contains(arr2, len2, arr1[i]) && !contains(result, count, arr1[i])) {
            result[count] = arr1[i];
            count++;
        }
    }

    if (count == 0) {
        free(result);
        return NULL;
    }

    if (count < cap) {
        int *shrunk = realloc(result, count * sizeof(*shrunk));
        if (shrunk != NULL) {
            result = shrunk;
        }
    }

    *result_len = count;
    return result;
}

static void print_result(const int *result, size_t result_len)
{
    putchar('[');
    for (size_t i = 0; i < result_len; i++) {
        if (i > 0) {
            fputs(", ", stdout);
        }
        printf("%d", result[i]);
    }
    fputs("]\n", stdout);
    fflush(stdout);
}

static void run_test(const int *arr1, size_t len1,
                     const int *arr2, size_t len2)
{
    size_t result_len = 0;
    int *result = intersection(arr1, len1, arr2, len2, &result_len);

    if (result == NULL || result_len == 0) {
        fputs("[]\n", stdout);
        fflush(stdout);
        free(result);
        return;
    }

    print_result(result, result_len);
    free(result);
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);

    int t0_a[] = {1, 2, 3, 4, 8, 9};
    int t0_b[] = {9, 8, 2, 1};
    run_test(t0_a, sizeof(t0_a) / sizeof(t0_a[0]),
             t0_b, sizeof(t0_b) / sizeof(t0_b[0]));

    int t1_a[] = {3, 5, 7, 9, 11};
    int t1_b[] = {9, 7, 5, 3};
    run_test(t1_a, sizeof(t1_a) / sizeof(t1_a[0]),
             t1_b, sizeof(t1_b) / sizeof(t1_b[0]));

    int t2_a[] = {10, 20, 30};
    int t2_b[] = {10, 40, 50};
    run_test(t2_a, sizeof(t2_a) / sizeof(t2_a[0]),
             t2_b, sizeof(t2_b) / sizeof(t2_b[0]));

    return EXIT_SUCCESS;
}