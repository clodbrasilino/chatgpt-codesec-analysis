#include <stdio.h>
#include <stdlib.h>

int value_exists_in_sequence(const int *sequence, size_t length, int value) {
    if (sequence == NULL && length > 0) {
        return 0;
    }
    
    for (size_t i = 0; i < length; i++) {
        if (sequence[i] == value) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int sequence[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(sequence) / sizeof(sequence[0]);
    int value_to_find = 3;
    
    if (value_exists_in_sequence(sequence, length, value_to_find)) {
        printf("Value %d found in sequence.\n", value_to_find);
    } else {
        printf("Value %d not found in sequence.\n", value_to_find);
    }
    
    value_to_find = 10;
    
    if (value_exists_in_sequence(sequence, length, value_to_find)) {
        printf("Value %d found in sequence.\n", value_to_find);
    } else {
        printf("Value %d not found in sequence.\n", value_to_find);
    }
    
    return EXIT_SUCCESS;
}