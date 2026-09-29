#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare_ints(const void *a, const void *b) {
    const int *arg1 = (const int *)a;
    const int *arg2 = (const int *)b;
    
    if (*arg1 < *arg2) {
        return -1;
    }
    if (*arg1 > *arg2) {
        return 1;
    }
    return 0;
}

bool find_most_frequent(const int *array, size_t size, int *result) {
    if (array == NULL || size == 0 || result == NULL) {
        return false;
    }

    int *sorted_array = (int *)malloc(size * sizeof(int));
    if (sorted_array == NULL) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        sorted_array[i] = array[i];
    }

    qsort(sorted_array, size, sizeof(int), compare_ints);

    int max_count = 1;
    int current_count = 1;
    int max_item = sorted_array[0];

    for (size_t i = 1; i < size; i++) {
        if (sorted_array[i] == sorted_array[i - 1]) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
                max_item = sorted_array[i - 1];
            }
            current_count = 1;
        }
    }

    if (current_count > max_count) {
        max_item = sorted_array[size - 1];
    }

    *result = max_item;
    
    free(sorted_array);
    sorted_array = NULL;

    return true;
}

int main(void) {
    const int data[] = {4, 1, 3, 2, 3, 4, 1, 3, 5, 3};
    const size_t size = sizeof(data) / sizeof(data[0]);
    int most_frequent_item = 0;

    if (find_most_frequent(data, size, &most_frequent_item)) {
        if (printf("%d\n", most_frequent_item) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}