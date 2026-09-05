#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_frequency_difference(const int arr[], size_t n) {
    if (n == 0) {
        return 0;
    }

    int min_val = arr[0];
    int max_val = arr[0];

    for (size_t i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    size_t range_size = (size_t)max_val - (size_t)min_val + 1;
    size_t *freq = (size_t *)calloc(range_size, sizeof(size_t));
    if (freq == NULL) {
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < n; i++) {
        freq[arr[i] - min_val]++;
    }

    size_t max_freq = 0;
    size_t min_freq = SIZE_MAX;

    for (size_t i = 0; i < range_size; i++) {
        if (freq[i] > 0) {
            if (freq[i] > max_freq) {
                max_freq = freq[i];
            }
            if (freq[i] < min_freq) {
                min_freq = freq[i];
            }
        }
    }

    free(freq);

    return (int)(max_freq - min_freq);
}

int main(void) {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int difference = find_frequency_difference(arr, n);

    printf("%d\n", difference);

    return 0;
}