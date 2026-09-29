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

static int *intersection(const int *arr1, size_t size1,
                         const int *arr2, size_t size2,
                         size_t *result_size)
{
    int *result;
    size_t count;
    size_t i;

    if (result_size == NULL) {
        return NULL;
    }

    *result_size = 0;

    if (arr1 == NULL || arr2 == NULL || size1 == 0 || size2 == 0) {
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

static int *read_array(size_t *size, int *error)
{
    int *arr;
    long n;
    size_t count;
    size_t i;

    if (size == NULL || error == NULL) {
        return NULL;
    }

    *size = 0;
    *error = 0;

    if (scanf("%ld", &n) != 1) {
        *error = 1;
        return NULL;
    }

    if (n < 0) {
        *error = 1;
        return NULL;
    }

    if (n == 0) {
        return NULL;
    }

    count = (size_t)n;

    arr = malloc(count * sizeof(*arr));
    if (arr == NULL) {
        *error = 1;
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            *error = 1;
            return NULL;
        }
    }

    *size = count;
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
    int error1;
    int error2;

    size1 = 0;
    size2 = 0;
    result_size = 0;

    arr1 = read_array(&size1, &error1);
    if (error1) {
        return EXIT_FAILURE;
    }

    arr2 = read_array(&size2, &error2);
    if (error2) {
        free(arr1);
        return EXIT_FAILURE;
    }

    result = intersection(arr1, size1, arr2, size2, &result_size);

    free(arr1);
    free(arr2);

    if (result == NULL || result_size == 0) {
        free(result);
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