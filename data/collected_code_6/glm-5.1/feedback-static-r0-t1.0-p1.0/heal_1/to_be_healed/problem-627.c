#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_smallest_missing(int *arr, size_t size) {
    int *present = NULL;
    size_t i;
    int max_val = 0;
    int result;

    if (size == 0 || arr == NULL) {
        return 1;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    if (max_val <= 0) {
        return 1;
    }

    present = (int *)calloc(max_val + 1, sizeof(int));
    if (present == NULL) {
        return 1;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] > 0) {
            present[arr[i]] = 1;
        }
    }

    result = max_val + 1;
    for (i = 1; i <= (size_t)max_val; i++) {
        if (present[i] == 0) {
            result = (int)i;
            break;
        }
    }

    free(present);
    return result;
}

int main(void) {
    int arr1[] = {3, 4, -1, 1};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int res1 = find_smallest_missing(arr1, size1);
    printf("%d\n", res1);

    int arr2[] = {1, 2, 0};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int res2 = find_smallest_missing(arr2, size2);
    printf("%d\n", res2);

    int arr3[] = {7, 8, 9, 11, 12};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int res3 = find_smallest_missing(arr3, size3);
    printf("%d\n", res3);

    int arr4[] = {-5, -2, -3};
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);
    int res4 = find_smallest_missing(arr4, size4);
    printf("%d\n", res4);

    return 0;
}