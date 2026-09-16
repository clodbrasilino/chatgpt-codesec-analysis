#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void counting_sort(int *array, size_t size) {
    if (array == NULL || size < 2) {
        return;
    }

    int max_val = array[0];
    int min_val = array[0];
    for (size_t i = 1; i < size; i++) {
        if (array[i] > max_val) {
            max_val = array[i];
        }
        if (array[i] < min_val) {
            min_val = array[i];
        }
    }

    size_t range = (size_t)(max_val - min_val) + 1;
    if (range > SIZE_MAX / sizeof(int)) {
        return;
    }

    size_t count_size = range * sizeof(size_t);
    size_t *count = (size_t *)malloc(count_size);
    if (count == NULL) {
        return;
    }
    memset(count, 0, count_size);

    for (size_t i = 0; i < size; i++) {
        count[array[i] - min_val]++;
    }

    for (size_t i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    int *output = (int *)malloc(size * sizeof(int));
    if (output == NULL) {
        free(count);
        return;
    }

    for (size_t i = size; i > 0; i--) {
        size_t count_index = array[i - 1] - min_val;
        count[count_index]--;
        output[count[count_index]] = array[i - 1];
    }

    memcpy(array, output, size * sizeof(int));

    free(count);
    free(output);
}

int main(void) {
    int array[] = {4, -2, 1, 6, -5, 3, 0, -2, 1};
    size_t size = sizeof(array) / sizeof(array[0]);

    counting_sort(array, size);

    for (size_t i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}