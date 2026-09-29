#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_smallest(int *list, size_t size) {
    if (list == NULL || size == 0) {
        return INT_MIN;
    }

    int smallest = list[0];
    for (size_t i = 1; i < size; i++) {
        if (list[i] < smallest) {
            smallest = list[i];
        }
    }

    return smallest;
}

int main(void) {
    int list[] = {5, 2, 9, 1, 5, 6};
    size_t size = sizeof(list) / sizeof(list[0]);

    int result = find_smallest(list, size);

    printf("%d\n", result);

    return 0;
}