#include <stdio.h>
#include <stdlib.h>

int find_last_occurrence(const int *array, int size, int target) {
    int index = -1;
    for (int i = 0; i < size; ++i) {
        if (array[i] == target) {
            index = i;
        }
    }
    return index;
}

int main() {
    int array[] = {1, 2, 4, 4, 6, 8, 8, 8, 10};
    int size = sizeof(array) / sizeof(array[0]);
    int targets[] = {3, 9, 6, 8};
    int num_targets = sizeof(targets) / sizeof(targets[0]);

    for (int i = 0; i < num_targets; ++i) {
        int index = find_last_occurrence(array, size, targets[i]);
        if (index != -1) {
            printf("Last occurrence of %d is at index %d\n", targets[i], index);
        } else {
            printf("%d not found in the array\n", targets[i]);
        }
    }

    return 0;
}