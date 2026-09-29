#include<stdio.h>
#include<stdlib.h>

int longestSubSeq(int* arr, int n) {
    int temp[10000] = {0};

    int max_val = 0;

    for (int i = 0; i < n; i++) {
        temp[arr[i]]++;
        if (arr[i] > max_val) max_val = arr[i];
    }

    int max_count = 0;
    for (int i = 0; i < max_val; i++) {
        if (temp[i] != 0 && temp[i + 1] != 0) {
            int count = 0;
            int j = i;
            while (temp[j] != 0) {
                count++;
                j++;
            }

            if (count > max_count) {
                max_count = count;
            }
        }
    }

    return max_count;
}

int main() {
    int arr[] = {1, 9, 3, 10, 4, 20, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of the Longest contiguous subsequence is %d", longestSubSeq(arr, n));
    return 0;
}
