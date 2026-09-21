#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

bool is_subset(const int *arr1, size_t n1, const int *arr2, size_t n2)
{
    int *sorted;
    size_t i;
    size_t bytes;
    bool result = true;

    if (n2 == 0) {
        return true;
    }
    if (arr1 == NULL || arr2 == NULL || n1 == 0) {
        return false;
    }
    if (n1 > SIZE_MAX / sizeof(*sorted)) {
        return false;
    }

    bytes = n1 * sizeof(*sorted);

    sorted = malloc(bytes);
    if (sorted == NULL) {
        return false;
    }

    for (i = 0; i < n1; i++) {
        sorted[i] = arr1[i];
    }

    qsort(sorted, n1, sizeof(*sorted), compare_ints);

    for (i = 0; i < n2; i++) {
        if (bsearch(&arr2[i], sorted, n1, sizeof(*sorted), compare_ints) == NULL) {
            result = false;
            break;
        }
    }

    free(sorted);
    return result;
}

int main(void)
{
    int arr1[] = {11, 1, 13, 21, 3, 7};
    int arr2[] = {11, 3, 7, 1};
    int arr3[] = {11, 3, 7, 1, 99};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);

    if (is_subset(arr1, n1, arr2, n2)) {
        if (printf("True\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("False\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (is_subset(arr1, n1, arr3, n3)) {
        if (printf("True\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("False\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}