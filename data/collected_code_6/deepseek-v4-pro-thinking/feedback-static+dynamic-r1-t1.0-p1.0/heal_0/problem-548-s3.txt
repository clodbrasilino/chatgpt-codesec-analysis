#include <stdio.h>
#include <stdlib.h>

static int lower_bound(const int *arr, int size, int key) {
    int left = 0;
    int right = size;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int longestIncreasingSubsequence(const int *nums, int n) {
    if (nums == NULL || n <= 0) {
        return 0;
    }

    int *tails = malloc((size_t)n * sizeof(*tails));
    if (tails == NULL) {
        return -1;
    }

    int len = 0;
    for (int i = 0; i < n; ++i) {
        int pos = lower_bound(tails, len, nums[i]);
        tails[pos] = nums[i];
        if (pos == len) {
            ++len;
        }
    }

    free(tails);
    return len;
}

int main(void) {
    int sequence[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int length = (int)(sizeof(sequence) / sizeof(sequence[0]));

    int result = longestIncreasingSubsequence(sequence, length);
    if (result < 0) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("%d\n", result);
    return 0;
}