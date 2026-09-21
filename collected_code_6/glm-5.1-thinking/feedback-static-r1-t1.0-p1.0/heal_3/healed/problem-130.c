#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int compare_ints(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

int find_max_frequency(const int *list, size_t length, int *out_item) {
    if (list == NULL || out_item == NULL || length == 0) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        return -2;
    }

    size_t byte_size = length * sizeof(int);
    int *temp = malloc(byte_size);
    if (temp == NULL) {
        return -2;
    }

    for (size_t i = 0; i < length; i++) {
        temp[i] = list[i];
    }

    qsort(temp, length, sizeof(int), compare_ints);

    size_t max_count = 1;
    size_t current_count = 1;
    int max_item = temp[0];

    for (size_t i = 1; i < length; i++) {
        if (temp[i] == temp[i - 1]) {
            current_count++;
        } else {
            current_count = 1;
        }

        if (current_count > max_count) {
            max_count = current_count;
            max_item = temp[i];
        }
    }

    free(temp);

    *out_item = max_item;
    return 0;
}

int main(void) {
    int arr[] = {1, 3, 2, 1, 4, 1, 3, 3, 3};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    int result;

    int ret = find_max_frequency(arr, len, &result);

    if (ret == 0) {
        printf("Item with maximum frequency: %d\n", result);
    } else {
        printf("Error finding maximum frequency item: %d\n", ret);
    }

    return 0;
}