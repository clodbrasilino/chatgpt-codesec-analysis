#include <stdio.h>
#include <stdlib.h>

int find_frequency_difference(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }

    int max_val = arr[0];
    int min_val = arr[0];

    for (size_t i = 1; i < size; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    int range = max_val - min_val + 1;
    if (range <= 0) {
        return -1;
    }

    int *freq = (int *)calloc(range, sizeof(int));
    if (freq == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; ++i) {
        freq[arr[i] - min_val]++;
    }

    int max_freq = -1;
    int min_freq = -1;

    for (int i = 0; i < range; ++i) {
        if (freq[i] > 0) {
            if (max_freq == -1 || freq[i] > max_freq) {
                max_freq = freq[i];
            }
            if (min_freq == -1 || freq[i] < min_freq) {
                min_freq = freq[i];
            }
        }
    }

    free(freq);

    if (max_freq == -1 || min_freq == -1) {
        return -1;
    }

    return max_freq - min_freq;
}

int main(void) {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int diff = find_frequency_difference(arr, size);

    if (diff != -1) {
        printf("Difference between highest and least frequencies: %d\n", diff);
    } else {
        printf("Error processing the array.\n");
    }

    return 0;
}