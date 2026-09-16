#include <stdio.h>
#include <stdlib.h>

static int has_majority_element(const int *array, size_t length, int value)
{
    size_t left = 0;
    size_t right = length;

    if (array == NULL || length == 0) {
        return 0;
    }

    while (left < right) {
        size_t middle = left + (right - left) / 2;

        if (array[middle] < value) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left < length && array[left] == value &&
           length / 2 < length - left &&
           array[left + length / 2] == value;
}

int main(void)
{
    const int array[] = {1, 2, 2, 2, 2, 3, 4};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const int value = 2;

    if (has_majority_element(array, length, value)) {
        printf("%d is a majority element.\n", value);
    } else {
        printf("%d is not a majority element.\n", value);
    }

    return EXIT_SUCCESS;
}