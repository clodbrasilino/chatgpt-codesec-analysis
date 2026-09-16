#include <stdio.h>
#include <stdlib.h>

int find_frequency_difference(int arr[], int n) {
    if (n <= 0) {
        return 0;
    }

    int min_val = arr[0];
    int max_val = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    int range = max_val - min_val + 1;

    if (range <= 0) {
        int count = 1;
        for (int i = 1; i < n; i++) {
            if (arr[i] != arr[0]) {
                count++;
            }
        }
        if (count == 1) {
            return 0;
        }
        int *freq = (int *)malloc(count * sizeof(int));
        if (freq == NULL) {
            return -1;
        }
        for (int i = 0; i < count; i++) {
            freq[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            freq[i % count]++;
        }
        int min_freq = n;
        int max_freq = 0;
        for (int i = 0; i < count; i++) {
            if (freq[i] > 0) {
                if (freq[i] < min_freq) {
                    min_freq = freq[i];
                }
                if (freq[i] > max_freq) {
                    max_freq = freq[i];
                }
            }
        }
        free(freq);
        return max_freq - min_freq;
    }

    int *freq = (int *)malloc(range * sizeof(int));
    if (freq == NULL) {
        return -1;
    }

    for (int i = 0; i < range; i++) {
        freq[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        freq[arr[i] - min_val]++;
    }

    int min_freq = n;
    int max_freq = 0;

    for (int i = 0; i < range; i++) {
        if (freq[i] > 0) {
            if (freq[i] < min_freq) {
                min_freq = freq[i];
            }
            if (freq[i] > max_freq) {
                max_freq = freq[i];
            }
        }
    }

    free(freq);

    return max_freq - min_freq;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int difference = find_frequency_difference(arr, n);

    printf("%d\n", difference);

    return 0;
}