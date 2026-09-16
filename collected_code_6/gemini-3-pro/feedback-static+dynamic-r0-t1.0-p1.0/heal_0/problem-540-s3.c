#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_frequency_difference(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return -1; 
    }

    int max_val = array[0];
    for (size_t i = 1; i < size; ++i) {
        if (array[i] > max_val) {
            max_val = array[i];
        }
    }

    int *freq = (int *)calloc((size_t)(max_val + 1), sizeof(int));
    if (freq == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; ++i) {
        if (array[i] < 0) {
            free(freq);
            return -1; 
        }
        freq[array[i]]++;
    }

    int highest_freq = 0;
    int least_freq = INT_MAX;

    for (int i = 0; i <= max_val; ++i) {
        if (freq[i] > 0) {
            if (freq[i] > highest_freq) {
                highest_freq = freq[i];
            }
            if (freq[i] < least_freq) {
                least_freq = freq[i];
            }
        }
    }

    free(freq);

    if (least_freq == INT_MAX) {
        return 0;
    }

    return highest_freq - least_freq;
}

int main(void) {
    int array[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    size_t size = sizeof(array) / sizeof(array[0]);

    int result = find_frequency_difference(array, size);
    if (result != -1) {
        printf("Difference between highest and least frequency: %d\n", result);
    } else {
        printf("Error processing the array.\n");
    }

    return 0;
}