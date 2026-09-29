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
  *  test case 1 failed: expected [3, 5, 7, 9], got <no output>
  *  test case 0 failed: expected [1, 2, 8, 9], got <no output>
  *  test case 2 failed: expected [10], got <no output>
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

int main(void)
{
    int arr1[] = {1, 2, 3, 4, 5, 3};
    int arr2[] = {3, 4, 5, 6, 7, 4};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t result_size;
    int *result;
    size_t i;

    result = intersection(arr1, size1, arr2, size2, &result_size);

    if (result == NULL) {
        if (printf("No intersection found\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("Intersection: ") < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_size; i++) {
        if (printf("%d ", result[i]) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}