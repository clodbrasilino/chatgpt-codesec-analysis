#include <stdio.h>
#include <stdlib.h>

int find_max_frequency(const int *list, size_t size, int *max_item) {
    if (list == NULL || size == 0 || max_item == NULL) {
        return -1;
    }

    int *items = malloc(size * sizeof(int));
    int *counts = malloc(size * sizeof(int));
    if (items == NULL || counts == NULL) {
        free(items);
        free(counts);
        return -1;
    }

    size_t unique_count = 0;
    for (size_t i = 0; i < size; i++) {
        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (items[j] == list[i]) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            items[unique_count] = list[i];
            counts[unique_count] = 1;
            unique_count++;
        }
    }

    int max_count = 0;
    *max_item = items[0];
    for (size_t i = 0; i < unique_count; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            *max_item = items[i];
        }
    }

    free(items);
    free(counts);
    return 0;
}

int main(void) {
    int list[] = {1, 3, 2, 1, 4, 1, 3, 3, 3};
    size_t size = sizeof(list) / sizeof(list[0]);
    int max_item;

    int result = find_max_frequency(list, size, &max_item);
    if (result == 0) {
        printf("%d\n", max_item);
    }

    return 0;
}