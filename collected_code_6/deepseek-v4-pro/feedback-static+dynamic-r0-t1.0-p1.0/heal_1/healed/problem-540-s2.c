#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VAL 1000000

int find_frequency_difference(const int *arr, int size) {
    if (size == 0) {
        return 0;
    }

    int *freq = (int *)calloc(MAX_VAL, sizeof(int));
    if (freq == NULL) {
        return -1;
    }

    int i;
    for (i = 0; i < size; i++) {
        if (arr[i] >= 0 && arr[i] < MAX_VAL) {
            freq[arr[i]]++;
        }
    }

    int min_freq = INT_MAX;
    int max_freq = 0;

    for (i = 0; i < MAX_VAL; i++) {
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

    if (min_freq == INT_MAX) {
        return 0;
    }

    return max_freq - min_freq;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 1, 2, 3, 1, 2, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = find_frequency_difference(arr, size);
    printf("%d\n", result);

    return 0;
}