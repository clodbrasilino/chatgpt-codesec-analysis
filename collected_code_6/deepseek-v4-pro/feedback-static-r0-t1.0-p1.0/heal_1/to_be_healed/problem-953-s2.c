#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int minSubsetsWithDistinctElements(int arr[], int n) {
    if (n <= 0) return 0;

    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    int *freq = (int *)calloc(max_val + 1, sizeof(int));
    if (freq == NULL) return -1;

    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0 && arr[i] <= max_val) {
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
    int arr1[] = {1, 2, 2, 3, 3, 3};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Minimum subsets: %d\n", minSubsetsWithDistinctElements(arr1, n1));

    int arr2[] = {5, 5, 5, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("Minimum subsets: %d\n", minSubsetsWithDistinctElements(arr2, n2));

    int arr3[] = {1, 2, 3, 4};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("Minimum subsets: %d\n", minSubsetsWithDistinctElements(arr3, n3));

    int arr4[] = {};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("Minimum subsets: %d\n", minSubsetsWithDistinctElements(arr4, n4));

    return 0;
}