#include <stdio.h>
#include <stdbool.h>

bool has_consecutive_numbers(const int *array, size_t size) {
    if (array == NULL || size < 2) {
        return false;
    }

    for (size_t i = 1; i < size; ++i) {
        if (array[i] == array[i - 1] + 1 || array[i] == array[i - 1] - 1) {
            return true;
        }
    }

    return false;
}

int main(void) {
    int list1[] = {1, 5, 8, 9, 12};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    
    int list2[] = {2, 4, 6, 8, 10};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);

    if (has_consecutive_numbers(list1, size1)) {
        printf("List 1 contains consecutive numbers.\n");
    } else {
        printf("List 1 does not contain consecutive numbers.\n");
    }

    if (has_consecutive_numbers(list2, size2)) {
        printf("List 2 contains consecutive numbers.\n");
    } else {
        printf("List 2 does not contain consecutive numbers.\n");
    }

    return 0;
}