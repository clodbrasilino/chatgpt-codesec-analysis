#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_greater_than_all(int number, const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return false; 
    }

    for (size_t i = 0; i < size; ++i) {
        if (number <= array[i]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int array[] = {1, 5, 8, 12, 4};
    size_t size = sizeof(array) / sizeof(array[0]);
    int number = 15;

    if (is_greater_than_all(number, array, size)) {
        printf("The number %d is greater than all elements in the array.\n", number);
    } else {
        printf("The number %d is not greater than all elements in the array.\n", number);
    }

    number = 10;
    if (is_greater_than_all(number, array, size)) {
        printf("The number %d is greater than all elements in the array.\n", number);
    } else {
        printf("The number %d is not greater than all elements in the array.\n", number);
    }

    return 0;
}