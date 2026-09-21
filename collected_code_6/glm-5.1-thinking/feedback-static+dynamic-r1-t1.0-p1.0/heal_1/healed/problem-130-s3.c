#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int compare_int(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int find_max_freq_item(const int *list, size_t size, int *result) {
    if (list == NULL || size == 0 || result == NULL) {
        return -1;
    }

    if (size > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    int *copy = malloc(size * sizeof(int));
    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, list, size * sizeof(int));
    qsort(copy, size, sizeof(int), compare_int);

    size_t max_freq = 1;
    int max_val = copy[0];
    size_t current_freq = 1;

    for (size_t i = 1; i < size; i++) {
        if (copy[i] == copy[i - 1]) {
            current_freq++;
        } else {
            current_freq = 1;
        }

        if (current_freq > max_freq) {
            max_freq = current_freq;
            max_val = copy[i];
        }
    }

    free(copy);

    *result = max_val;
    return 0;
}

int main(void) {
    int list[] = {1, 3, 2, 1, 4, 1, 3, 2, 1};
    size_t size = sizeof(list) / sizeof(list[0]);
    int result;

    if (find_max_freq_item(list, size, &result) == 0) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Error\n");
        return 1;
    }

    return 0;
}