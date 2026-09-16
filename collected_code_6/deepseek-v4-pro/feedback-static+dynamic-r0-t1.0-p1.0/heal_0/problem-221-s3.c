#include <stdio.h>
#include <stdlib.h>

int find_first_even(const int *numbers, size_t length, int *result) {
    if (numbers == NULL || result == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i < length; i++) {
        if (numbers[i] % 2 == 0) {
            *result = numbers[i];
            return 0;
        }
    }
    
    return -1;
}

int main(void) {
    int numbers[] = {1, 3, 5, 7, 8, 9, 10};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int result = 0;
    
    if (find_first_even(numbers, length, &result) == 0) {
        printf("First even number: %d\n", result);
    } else {
        printf("No even number found\n");
    }
    
    return 0;
}