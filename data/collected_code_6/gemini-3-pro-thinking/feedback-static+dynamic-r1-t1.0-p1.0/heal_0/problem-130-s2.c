#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *a, const void *b) {
    const int *int_a = (const int *)a;
    const int *int_b = (const int *)b;
    
    if (*int_a < *int_b) {
        return -1;
    }
    if (*int_a > *int_b) {
        return 1;
    }
    return 0;
}

int find_max_frequency(const int *arr, size_t size, int *out_val) {
    if (arr == NULL || out_val == NULL || size == 0) {
        return -1;
    }

    int *copy = (int *)malloc(size * sizeof(int));
    if (copy == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; ++i) {
        copy[i] = arr[i];
    }

    qsort(copy, size, sizeof(int), compare_ints);

    int max_val = copy[0];
    size_t max_count = 1;

    int current_val = copy[0];
    size_t current_count = 1;

    for (size_t i = 1; i < size; ++i) {
        if (copy[i] == current_val) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
                max_val = current_val;
            }
            current_val = copy[i];
            current_count = 1;
        }
    }

    if (current_count > max_count) {
        max_val = current_val;
    }

    *out_val = max_val;
    free(copy);

    return 0;
}

int main(void) {
    const int data[] = {4, 1, 3, 2, 1, 4, 1, 3, 2, 3, 3, 3};
    size_t size = sizeof(data) / sizeof(data[0]);
    int most_frequent = 0;

    if (find_max_frequency(data, size, &most_frequent) == 0) {
        printf("%d\n", most_frequent);
    } else {
        fprintf(stderr, "Error processing the array.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}