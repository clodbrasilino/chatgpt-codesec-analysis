#include <stdio.h>
#include <stddef.h>

int value_exists(const int *sequence, size_t length, int value) {
    if (sequence == NULL) {
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
    int sequence[] = {3, 7, 2, 9, 5, 1, 8, 4, 6};
    size_t length = sizeof(sequence) / sizeof(sequence[0]);
    
    int values_to_check[] = {5, 10, 3, 0};
    
    for (size_t i = 0; i < sizeof(values_to_check) / sizeof(values_to_check[0]); i++) {
        printf("Value %d exists: %s\n", 
               values_to_check[i], 
               value_exists(sequence, length, values_to_check[i]) ? "yes" : "no");
    }
    
    return 0;
}