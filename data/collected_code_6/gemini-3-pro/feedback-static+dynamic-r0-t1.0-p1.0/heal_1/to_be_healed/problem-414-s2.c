#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'sequence' can be declared as const array [constParameter]
 */
bool valueExists(int sequence[], int size, int value) {
    if (sequence == NULL || size <= 0) {
        return false;
    }
    
    for (int i = 0; i < size; i++) {
        if (sequence[i] == value) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    int sequence[] = {5, 10, 15, 20, 25};
    int size = sizeof(sequence) / sizeof(sequence[0]);
    int searchValue = 15;
    
    if (valueExists(sequence, size, searchValue)) {
        printf("Value %d exists in the sequence.\n", searchValue);
    } else {
        printf("Value %d does not exist in the sequence.\n", searchValue);
    }
    
    searchValue = 30;
    
    if (valueExists(sequence, size, searchValue)) {
        printf("Value %d exists in the sequence.\n", searchValue);
    } else {
        printf("Value %d does not exist in the sequence.\n", searchValue);
    }
    
    return 0;
}