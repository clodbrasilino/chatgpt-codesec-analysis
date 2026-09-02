#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int minSubsetsWithDistinctElements(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    int *freq = (int *)calloc(max_val + 1, sizeof(int));
    if (freq == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            freq[arr[i]]++;
        }
    }

    int max_freq = 0;
    for (int i = 0; i <= max_val; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
        }
    }

    free(freq);
    return max_freq;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", minSubsetsWithDistinctElements(arr1, n1));

    int arr2[] = {1, 2, 3, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", minSubsetsWithDistinctElements(arr2, n2));

    int arr3[] = {1, 1, 1, 1};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", minSubsetsWithDistinctElements(arr3, n3));

    int arr4[] = {5, 5, 5, 5, 5};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", minSubsetsWithDistinctElements(arr4, n4));

    int arr5[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("%d\n", minSubsetsWithDistinctElements(arr5, n5));

    printf("%d\n", minSubsetsWithDistinctElements(NULL, 0));

    return 0;
}