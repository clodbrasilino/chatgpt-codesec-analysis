#include <stdio.h>
#include <stdlib.h>

long long sum_in_range(const int* list, size_t length, size_t start, size_t end) {
    long long sum = 0;
    
    if (list == NULL || length == 0) {
        return 0;
    }
    
    if (start >= length) {
        return 0;
    }
    
    if (end >= length) {
        end = length - 1;
    }
    
    if (start > end) {
        return 0;
    }
    
    for (size_t i = start; i <= end; ++i) {
        sum += list[i];
    }
    
    return sum;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    size_t start = 2;
    size_t end = 6;
    
    long long result = sum_in_range(numbers, length, start, end);
    
    printf("Sum: %lld\n", result);
    
    return 0;
}