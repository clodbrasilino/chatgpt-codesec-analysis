#include <stdio.h>
#include <stdlib.h>

int find_first_even(const int *numbers, size_t count, int *result) {
    if (numbers == NULL || result == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] % 2 == 0) {
            *result = numbers[i];
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    int numbers[] = {1, 3, 5, 7, 8, 10, 12};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int result;
    
    if (find_first_even(numbers, count, &result)) {
        printf("First even number: %d\n", result);
    } else {
        printf("No even number found\n");
    }
    
    return 0;
}