#include <stdbool.h>
#include <stdio.h>

bool is_monotonic(const int *array, int size) {
    bool increasing = true;
    bool decreasing = true;

    for (int i = 1; i < size; ++i) {
        if (array[i] > array[i - 1]) {
            decreasing = false;
        } else if (array[i] < array[i - 1]) {
            increasing = false;
        }
    }

    return increasing || decreasing;
}

int main() {
    int array1[] = {1, 2, 4, 20};
    int array2[] = {1, 20, 4, 10};
    int array3[] = {10, 5, 2, 1};

    int size1 = sizeof(array1) / sizeof(array1[0]);
    int size2 = sizeof(array2) / sizeof(array2[0]);
    int size3 = sizeof(array3) / sizeof(array3[0]);

    if (is_monotonic(array1, size1)) {
        printf("Array 1 is monotonic.\n");
    } else {
        printf("Array 1 is not monotonic.\n");
    }

    if (is_monotonic(array2, size2)) {
        printf("Array 2 is monotonic.\n");
    } else {
        printf("Array 2 is not monotonic.\n");
    }

    if (is_monotonic(array3, size3)) {
        printf("Array 3 is monotonic.\n");
    } else {
        printf("Array 3 is not monotonic.\n");
    }

    return 0;
}