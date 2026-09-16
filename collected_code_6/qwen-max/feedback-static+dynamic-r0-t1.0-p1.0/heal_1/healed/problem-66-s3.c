#include <stdio.h>
#include <stdlib.h>

int count_positive(const int *nums, int len) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        if (nums[i] > 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, -2, 3, -4, 5, 6, -7, 8, 9, -10};
    int len = sizeof(arr) / sizeof(arr[0]);
    int positive_count = count_positive(arr, len);
    printf("Count of positive numbers: %d\n", positive_count);
    return 0;
}