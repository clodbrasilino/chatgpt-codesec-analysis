#include <stdio.h>
#include <stdlib.h>

size_t lis_binary_search(const int *arr, size_t len, int target) {
    size_t left = 0;
    size_t right = len;
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

size_t longest_increasing_subsequence(const int *seq, size_t n) {
    if (n == 0) {
        return 0;
    }
    int *tails = malloc(n * sizeof(int));
    if (tails == NULL) {
        return 0;
    }
    size_t length = 0;
    for (size_t i = 0; i < n; i++) {
        size_t pos = lis_binary_search(tails, length, seq[i]);
        tails[pos] = seq[i];
        if (pos == length) {
            length++;
        }
    }
    free(tails);
    return length;
}

int main(void) {
    int seq[] = {10, 9, 2, 5, 3, 7, 101, 18};
    size_t n = sizeof(seq) / sizeof(seq[0]);
    size_t result = longest_increasing_subsequence(seq, n);
    printf("%zu\n", result);
    return 0;
}