#include <stdio.h>

int findMaxLength(const int arr[], int n) {
    int max = 1, curr = 1;
    int diff = arr[1] - arr[0];
    for (int i = 1; i < n - 1; i++) {
        if (arr[i + 1] - arr[i] == diff) {
            curr++;
        } else {
            if (curr > max) {
                max = curr;
            }
            curr = 1;
            diff = arr[i + 1] - arr[i];
        }
    }

    if (curr > max) {
        max = curr;
    }

    return max;
}

int main() {
    const int arr[] = {3, 8, 4, 5, 6, 2, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    int maxLength = findMaxLength(arr, n);

    printf("Maximum length of subsequence with adjacent difference: %d\n", maxLength);

    return 0;
}