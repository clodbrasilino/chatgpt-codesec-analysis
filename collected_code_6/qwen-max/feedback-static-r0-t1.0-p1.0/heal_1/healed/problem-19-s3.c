#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool contains_duplicate(const int *array, size_t array_size) {
    for (size_t i = 0; i < array_size; ++i) {
        for (size_t j = i + 1; j < array_size; ++j) {
            if (array[i] == array[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int data[] = {1, 2, 3, 4, 5, 2};
    size_t n = sizeof(data) / sizeof(data[0]);
    if (contains_duplicate(data, n)) {
        printf("Array contains duplicate elements.\n");
    } else {
        printf("Array does not contain duplicate elements.\n");
    }
    return 0;
}