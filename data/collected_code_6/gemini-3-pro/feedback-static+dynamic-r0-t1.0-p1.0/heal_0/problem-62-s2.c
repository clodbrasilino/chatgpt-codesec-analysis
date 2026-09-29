#include <stdio.h>
#include <limits.h>

int find_smallest(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return INT_MAX;
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
    int numbers[] = {5, 2, 9, 1, 7, 3, 8};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    int smallest = find_smallest(numbers, size);

    if (smallest != INT_MAX) {
        printf("The smallest number is: %d\n", smallest);
    } else {
        printf("The list is empty or invalid.\n");
    }

    return 0;
}