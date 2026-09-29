#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sum_non_repeated(int *arr, int size) {
    int *counts = NULL;
    int max = 0;
    int sum = 0;
    int i;

    if (arr == NULL || size <= 0) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] < 0) {
            return 0;
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    counts = (int *)calloc(max + 1, sizeof(int));
    if (counts == NULL) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        counts[arr[i]]++;
    }

    for (i = 0; i <= max; i++) {
        if (counts[i] == 1) {
            sum += i;
        }
    }

    free(counts);
    return sum;
}

int main(void) {
    int arr1[] = {1, 2, 3, 2, 5, 3, 7};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = sum_non_repeated(arr1, size1);
    printf("%d\n", result1);

    int arr2[] = {4, 4, 4, 4};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = sum_non_repeated(arr2, size2);
    printf("%d\n", result2);

    int arr3[] = {1, 2, 3, 4, 5};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = sum_non_repeated(arr3, size3);
    printf("%d\n", result3);

    int arr4[] = {0, 0, 1, 1, 2, 2};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    int result4 = sum_non_repeated(arr4, size4);
    printf("%d\n", result4);

    int result5 = sum_non_repeated(NULL, 5);
    printf("%d\n", result5);

    int arr6[] = {-1, 2, 3};
    int size6 = sizeof(arr6) / sizeof(arr6[0]);
    int result6 = sum_non_repeated(arr6, size6);
    printf("%d\n", result6);

    return 0;
}