#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool value_exists_in_sequence(const int *sequence, size_t length, int value) {
    if (sequence == NULL || length == 0) {
        return false;
    }
    
    for (size_t i = 0; i < length; i++) {
        if (sequence[i] == value) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    int numbers[] = {3, 7, 1, 9, 4, 6, 8, 2, 5, 0};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    
    int test_values[] = {5, 10, 0, 3, 11};
    size_t test_count = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < test_count; i++) {
        if (value_exists_in_sequence(numbers, length, test_values[i])) {
            printf("Value %d exists in the sequence.\n", test_values[i]);
        } else {
            printf("Value %d does not exist in the sequence.\n", test_values[i]);
        }
    }
    
    return 0;
}