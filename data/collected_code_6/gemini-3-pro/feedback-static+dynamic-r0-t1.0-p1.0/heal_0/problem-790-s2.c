#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool check_even_indices_even(const int *array, size_t size) {
    if (array == NULL && size > 0) {
        return false;
    }

    for (size_t i = 0; i < size; i += 2) {
        if (array[i] % 2 != 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int valid_array[] = {2, 1, 4, 3, 6, 5};
    size_t valid_size = sizeof(valid_array) / sizeof(valid_array[0]);

    if (check_even_indices_even(valid_array, valid_size)) {
        printf("Valid array: Every even index contains an even number.\n");
    } else {
        printf("Valid array: Condition not met.\n");
    }

    int invalid_array[] = {2, 1, 3, 3, 6, 5};
    size_t invalid_size = sizeof(invalid_array) / sizeof(invalid_array[0]);

    if (check_even_indices_even(invalid_array, invalid_size)) {
        printf("Invalid array: Every even index contains an even number.\n");
    } else {
        printf("Invalid array: Condition not met.\n");
    }

    return EXIT_SUCCESS;
}