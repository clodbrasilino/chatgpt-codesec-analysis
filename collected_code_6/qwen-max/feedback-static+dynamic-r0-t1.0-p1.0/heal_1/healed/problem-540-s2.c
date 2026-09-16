#include <stdio.h>
#include <limits.h>

int findDifference(const int *arr, int n) {
    int freq[101] = {0};
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 0 && arr[i] <= 100) {
            freq[arr[i]]++;
        }
    }

    int max_freq = INT_MIN;
    int min_freq = INT_MAX;

    for (int i = 0; i < 101; i++) {
        if (freq[i] > 0) {
            if (freq[i] > max_freq) max_freq = freq[i];
            if (freq[i] < min_freq) min_freq = freq[i];
        }
    }

    return max_freq - min_freq;
}

int main() {
    int arr[] = {1, 2, 3, 3, 2, 4, 4, 4, 5, 5, 5, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int diff = findDifference(arr, n);
    printf("The difference between the highest and least frequencies is: %d\n", diff);
    return 0;
}