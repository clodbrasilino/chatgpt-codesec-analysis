#include <stdio.h>
#include <stdlib.h>

int find_first_even(const int *numbers, size_t length, int *result) {
    if (numbers == NULL || result == NULL || length == 0) {
        return 0;
    }
    
    for (size_t i = 0; i < length; i++) {
        if (numbers[i] % 2 == 0) {
            *result = numbers[i];
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    int numbers[] = {1, 3, 5, 7, 8, 10};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int first_even;
    
    if (find_first_even(numbers, length, &first_even)) {
        printf("First even number: %d\n", first_even);
    } else {
        printf("No even number found\n");
    }
    
    return 0;
}