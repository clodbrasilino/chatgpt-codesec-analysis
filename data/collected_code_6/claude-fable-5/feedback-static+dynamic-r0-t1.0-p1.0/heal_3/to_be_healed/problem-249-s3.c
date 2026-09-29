#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *arr, size_t size, int value)
{
    size_t i;

    for (i = 0; i < size; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected [10], got <no output>
  *  test case 1 failed: expected [3, 5, 7, 9], got <no output>
  *  test case 0 failed: expected [1, 2, 8, 9], got <no output>
  */

static int *intersection(const int *arr1, size_t size1,
                         const int *arr2, size_t size2,
                         size_t *result_size)
{
    int *result;
    size_t count;
    size_t i;

    if (arr1 == NULL || arr2 == NULL || result_size == NULL) {
        return NULL;
    }

    *result_size = 0;

    if (size1 == 0 || size2 == 0) {
        return NULL;
    }

    result = malloc(size1 * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    count = 0;
    for (i = 0; i < size1; i++) {
        if (contains(arr2, size2, arr1[i]) &&
            !contains(result, count, arr1[i])) {
            result[count] = arr1[i];
            count++;
        }
    }

    if (count == 0) {
        free(result);
        return NULL;
    }

    *result_size = count;
    return result;
}

static int print_result(const int *result, size_t result_size)
{
    size_t i;

    if (printf("[") < 0) {
        return -1;
    }

    for (i = 0; i < result_size; i++) {
        if (i > 0) {
            if (printf(", ") < 0) {
                return -1;
            }
        }
        if (printf("%d", result[i]) < 0) {
            return -1;
        }
    }

    if (printf("]\n") < 0) {
        return -1;
    }

    return 0;
}

static int *read_array(size_t *size)
{
    int *arr;
    size_t n;
    size_t i;

    if (size == NULL) {
        return NULL;
    }

    if (scanf("%zu", &n) != 1) {
        return NULL;
    }

    if (n == 0) {
        *size = 0;
        return NULL;
    }

    arr = malloc(n * sizeof(*arr));
    if (arr == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return NULL;
        }
    }

    *size = n;
    return arr;
}

int main(void)
{
    int *arr1;
    int *arr2;
    size_t size1;
    size_t size2;
    size_t result_size;
    int *result;

    size1 = 0;
    size2 = 0;

    arr1 = read_array(&size1);
    if (arr1 == NULL && size1 != 0) {
        return EXIT_FAILURE;
    }

    arr2 = read_array(&size2);
    if (arr2 == NULL && size2 != 0) {
        free(arr1);
        return EXIT_FAILURE;
    }

    result = intersection(arr1, size1, arr2, size2, &result_size);

    free(arr1);
    free(arr2);

    if (result == NULL) {
        if (printf("[]\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (print_result(result, result_size) != 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}