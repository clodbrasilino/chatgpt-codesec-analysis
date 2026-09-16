#include <stdio.h>
#include <stdlib.h>

int find_first_duplicate(const int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return -1;
    }

    int *seen = (int *)calloc(100001, sizeof(int));
    if (seen == NULL) {
        return -1;
    }

    int result = -1;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] >= 0 && arr[i] <= 100000) {
            if (seen[arr[i]] == 1) {
                result = arr[i];
                break;
            }
            seen[arr[i]] = 1;
        }
    }

    free(seen);
    return result;
}

int main(void) {
    int arr1[] = {2, 5, 1, 2, 3, 5, 1};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int res1 = find_first_duplicate(arr1, size1);
    printf("%d\n", res1);

    int arr2[] = {2, 1, 3, 5, 3, 2};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int res2 = find_first_duplicate(arr2, size2);
    printf("%d\n", res2);

    int arr3[] = {1, 2, 3, 4, 5};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int res3 = find_first_duplicate(arr3, size3);
    printf("%d\n", res3);

    const int *arr4 = NULL;
    size_t size4 = 0;
    int res4 = find_first_duplicate(arr4, size4);
    printf("%d\n", res4);

    return 0;
}