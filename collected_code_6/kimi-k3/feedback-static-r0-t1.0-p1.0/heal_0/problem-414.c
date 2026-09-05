#include <stdio.h>
#include <stdbool.h>

bool value_exists(const int *sequence, size_t length, int target) {
    if (sequence == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < length; i++) {
        if (sequence[i] == target) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    int sequence[] = {10, 20, 30, 40, 50};
    size_t length = sizeof(sequence) / sizeof(sequence[0]);
    int target = 30;
    
    if (value_exists(sequence, length, target)) {
        printf("Value %d exists in the sequence.\n", target);
    } else {
        printf("Value %d does not exist in the sequence.\n", target);
    }
    
    return 0;
}