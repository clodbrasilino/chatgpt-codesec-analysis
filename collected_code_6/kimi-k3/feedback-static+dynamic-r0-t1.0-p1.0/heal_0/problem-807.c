#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int find_first_odd(const int *numbers, size_t size, int *result) {
    size_t i;
    
    if (numbers == NULL || result == NULL) {
        return 0;
    }
    
    for (i = 0; i < size; i++) {
        if (numbers[i] % 2 != 0) {
            *result = numbers[i];
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    int numbers[] = {2, 4, 6, 8, 9, 10, 12};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int result;
    int status;
    
    status = find_first_odd(numbers, size, &result);
    
    if (status == 1) {
        printf("First odd number: %d\n", result);
    } else {
        printf("No odd number found in the list.\n");
    }
    
    return EXIT_SUCCESS;
}