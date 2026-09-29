#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int minSubsets(int arr[], int n) {
    if (n == 0) {
        return 0;
    }

    qsort(arr, n, sizeof(int), compare);

    int max_count = 1;
    int current_count = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
            }
            current_count = 1;
        }
    }

    if (current_count > max_count) {
        max_count = current_count;
    }

    return max_count;
}

int main() {
    int arr[] = {1, 2, 3, 3, 4, 4, 4, 5};
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(arr)/sizeof(arr[0])', assigned value is 8
     */
    int n = sizeof(arr) / sizeof(arr[0]);

    /* Possible weaknesses found:
     *  Condition 'n<0' is always false [knownConditionTrueFalse]
     *  Condition 'n<0' is always false
     */
    if (n < 0) {
        return 1;
    }

    int result = minSubsets(arr, n);

    printf("%d\n", result);

    return 0;
}