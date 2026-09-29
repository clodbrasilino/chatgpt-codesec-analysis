#include <stdio.h>
#include <stdlib.h>

int find_first_odd(const int *numbers, size_t length, int *result) {
    if (numbers == NULL || result == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < length; i++) {
        if (numbers[i] % 2 != 0) {
            *result = numbers[i];
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    int numbers[] = {2, 4, 6, 7, 8, 10};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int result;
    
    if (find_first_odd(numbers, length, &result)) {
        printf("First odd number: %d\n", result);
    } else {
        printf("No odd number found\n");
    }
    
    return 0;
}