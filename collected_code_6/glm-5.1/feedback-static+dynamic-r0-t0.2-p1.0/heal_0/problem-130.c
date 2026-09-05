#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_frequency_item(int *list, size_t size) {
    if (list == NULL || size == 0) {
        return INT_MIN;
    }

    int *items = malloc(size * sizeof(int));
    int *counts = malloc(size * sizeof(int));
    if (items == NULL || counts == NULL) {
        free(items);
        free(counts);
        return INT_MIN;
    }

    size_t unique_size = 0;

    for (size_t i = 0; i < size; i++) {
        int found = 0;
        for (size_t j = 0; j < unique_size; j++) {
            if (items[j] == list[i]) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            items[unique_size] = list[i];
            counts[unique_size] = 1;
            unique_size++;
        }
    }

    int max_count = 0;
    int max_item = INT_MIN;

    for (size_t i = 0; i < unique_size; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            max_item = items[i];
        }
    }

    free(items);
    free(counts);

    return max_item;
}

int main(void) {
    int list[] = {1, 3, 2, 1, 4, 1, 3, 3, 3};
    size_t size = sizeof(list) / sizeof(list[0]);

    int result = find_max_frequency_item(list, size);

    printf("%d\n", result);

    return 0;
}