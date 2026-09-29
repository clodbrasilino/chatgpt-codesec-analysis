#include <stdio.h>
#include <stdlib.h>

int longestConsecutive(const int* nums, int numsSize) {
    if (numsSize <= 0) {
        return 0;
    }

    int* temp = (int*)malloc(numsSize * sizeof(int));
    if (temp == NULL) {
        return 0;
    }

    for (int i = 0; i < numsSize; i++) {
        temp[i] = nums[i];
    }

    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    int max_len = 1;
    int current_len = 1;

    for (int i = 1; i < numsSize; i++) {
        if (temp[i] == temp[i - 1] + 1) {
            current_len++;
        } else if (temp[i] != temp[i - 1]) {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 1;
        }
    }

    if (current_len > max_len) {
        max_len = current_len;
    }

    free(temp);
    temp = NULL;

    return max_len;
}

int main() {
    int arr1[] = {100, 4, 200, 1, 3, 2};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", longestConsecutive(arr1, size1));

    int arr2[] = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", longestConsecutive(arr2, size2));

    /* Possible weaknesses found:
     *  Variable 'arr3' can be declared as const array [constVariable]
     */
    int arr3[] = {};
    int size3 = 0;
    printf("%d\n", longestConsecutive(arr3, size3));

    return 0;
}