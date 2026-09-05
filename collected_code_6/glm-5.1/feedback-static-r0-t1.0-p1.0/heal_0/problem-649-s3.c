#include <stdio.h>
#include <stdlib.h>

int calculate_range_sum(const int *list, size_t size, size_t start, size_t end) {
    if (list == NULL) {
        return 0;
    }
    if (size == 0 || start > end) {
        return 0;
    }
    if (end >= size) {
        end = size - 1;
    }
    if (start >= size) {
        return 0;
    }
    
    int sum = 0;
    for (size_t i = start; i <= end; i++) {
        sum += list[i];
    }
    return sum;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t start = 2;
    size_t end = 5;
    
    int result = calculate_range_sum(numbers, size, start, end);
    printf("%d\n", result);
    
    return 0;
}