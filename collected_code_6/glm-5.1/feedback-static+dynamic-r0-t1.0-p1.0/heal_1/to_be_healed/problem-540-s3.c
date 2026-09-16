#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int find_frequency_difference(int *array, size_t size) {
    if (array == NULL || size == 0) {
        return -1;
    }

    size_t unique_count = 0;
    int *keys = (int *)malloc(size * sizeof(int));
    size_t *freqs = (size_t *)malloc(size * sizeof(size_t));

    if (keys == NULL || freqs == NULL) {
        free(keys);
        free(freqs);
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (keys[j] == array[i]) {
                freqs[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            keys[unique_count] = array[i];
            freqs[unique_count] = 1;
            unique_count++;
        }
    }

    size_t max_freq = 0;
    size_t min_freq = SIZE_MAX;

    for (size_t i = 0; i < unique_count; i++) {
        if (freqs[i] > max_freq) {
            max_freq = freqs[i];
        }
        if (freqs[i] < min_freq) {
            min_freq = freqs[i];
        }
    }

    free(keys);
    free(freqs);

    return (int)(max_freq - min_freq);
}

int main(void) {
    int arr1[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int diff1 = find_frequency_difference(arr1, size1);
    printf("%d\n", diff1);

    int arr2[] = {7, 7, 7, 7, 7};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int diff2 = find_frequency_difference(arr2, size2);
    printf("%d\n", diff2);

    int arr3[] = {10, 20, 30, 40, 50};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int diff3 = find_frequency_difference(arr3, size3);
    printf("%d\n", diff3);

    return 0;
}