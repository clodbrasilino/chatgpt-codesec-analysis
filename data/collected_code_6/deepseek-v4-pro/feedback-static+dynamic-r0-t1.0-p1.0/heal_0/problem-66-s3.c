#include <stdio.h>
#include <stdlib.h>

int count_positive_numbers(const int *list, size_t size) {
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] > 0) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int numbers[] = {-1, 2, -3, 4, 0, 5, -6, 7};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    
    int positive_count = count_positive_numbers(numbers, size);
    printf("Positive numbers count: %d\n", positive_count);
    
    return EXIT_SUCCESS;
}