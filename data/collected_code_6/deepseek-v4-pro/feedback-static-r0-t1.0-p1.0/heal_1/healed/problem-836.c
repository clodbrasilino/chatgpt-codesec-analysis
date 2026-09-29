#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max_subarray_length(const int arr[], int n) {
    if (n <= 0) {
        return 0;
    }

    int max_sum = arr[0];
    int current_sum = arr[0];
    int max_length = 1;
    int current_length = 1;
    int start = 0;

    for (int i = 1; i < n; i++) {
        if (current_sum < 0) {
            current_sum = arr[i];
            current_length = 1;
            start = i;
        } else {
            current_sum = current_sum + arr[i];
            current_length++;
        }

        if (current_sum > max_sum ||
            (current_sum == max_sum && current_length > max_length)) {
            max_sum = current_sum;
            max_length = current_length;
        }
        (void)start;
    }

    return max_length;
}

int main(void) {
    int arr1[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", max_subarray_length(arr1, n1));

    int arr2[] = {1, -2, 3, -1, 2, 1, -5, 4};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", max_subarray_length(arr2, n2));

    int arr3[] = {-1, -2, -3, -4, -5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", max_subarray_length(arr3, n3));

    int arr4[] = {5, 4, -1, 7, 8};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", max_subarray_length(arr4, n4));

    int arr5[] = {1};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("%d\n", max_subarray_length(arr5, n5));

    int arr6[] = {};
    int n6 = sizeof(arr6) / sizeof(arr6[0]);
    printf("%d\n", max_subarray_length(arr6, n6));

    return 0;
}