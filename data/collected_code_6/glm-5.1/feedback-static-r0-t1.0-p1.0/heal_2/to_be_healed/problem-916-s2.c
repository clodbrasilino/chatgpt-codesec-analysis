#include <stdio.h>
#include <stdlib.h>

int find_triplet(const int *arr, int n, int target) {
    if (arr == NULL || n < 3) {
        return 0;
    }

    int *sorted = malloc(n * sizeof(int));
    if (sorted == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n - 2; i++) {
        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            int current_sum = sorted[i] + sorted[left] + sorted[right];

            if (current_sum == target) {
                free(sorted);
                return 1;
            } else if (current_sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }

    free(sorted);
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'arr1' can be declared as const array [constVariable]
     */
    int arr1[] = {1, 4, 45, 6, 10, 8};
    int target1 = 22;
    int result1 = find_triplet(arr1, 6, target1);
    printf("%d\n", result1);

    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {1, 2, 3};
    int target2 = 6;
    int result2 = find_triplet(arr2, 3, target2);
    printf("%d\n", result2);

    /* Possible weaknesses found:
     *  Variable 'arr3' can be declared as const array [constVariable]
     */
    int arr3[] = {1, 2, 3};
    int target3 = 7;
    int result3 = find_triplet(arr3, 3, target3);
    printf("%d\n", result3);

    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as pointer to const [constVariablePointer]
     */
    int *arr4 = NULL;
    int target4 = 0;
    int result4 = find_triplet(arr4, 0, target4);
    printf("%d\n", result4);

    return 0;
}