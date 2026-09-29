#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_occurrences(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return INT_MIN;
    }

    int min_val = list[0];
    int max_val = list[0];

    for (size_t i = 1; i < size; i++) {
        if (list[i] < min_val) {
            min_val = list[i];
        }
        if (list[i] > max_val) {
            max_val = list[i];
        }
    }

    size_t range = (size_t)(max_val - min_val + 1);

    size_t *counts = (size_t *)calloc(range, sizeof(size_t));
    if (counts == NULL) {
        return INT_MIN;
    }

    for (size_t i = 0; i < size; i++) {
        counts[list[i] - min_val]++;
    }

    size_t max_count = 0;
    int max_item = list[0];

    for (size_t i = 0; i < range; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            max_item = (int)(i + min_val);
        }
    }

    free(counts);

    return max_item;
}

int main(void) {
    int list0[] = {1, 2, 2, 3, 4};
    size_t size0 = sizeof(list0) / sizeof(list0[0]);
    int result0 = find_max_occurrences(list0, size0);
    if (result0 != INT_MIN) {
        printf("%d\n", result0);
    }

    int list1[] = {5, 5, 5, 5, 5};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    int result1 = find_max_occurrences(list1, size1);
    if (result1 != INT_MIN) {
        printf("%d\n", result1);
    }

    int list2[] = {7, 8, 9, 8, 7};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    int result2 = find_max_occurrences(list2, size2);
    if (result2 != INT_MIN) {
        printf("%d\n", result2);
    }

    return 0;
}