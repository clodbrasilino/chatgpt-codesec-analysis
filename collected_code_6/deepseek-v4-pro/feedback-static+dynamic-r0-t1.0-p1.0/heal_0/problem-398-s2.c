#include <stdio.h>
#include <stdlib.h>

int sum_of_digits(int number) {
    int sum = 0;
    int temp = abs(number);
    
    while (temp > 0) {
        sum += temp % 10;
        temp /= 10;
    }
    
    if (sum == 0) {
        return 0;
    }
    
    return sum;
}

int* compute_digit_sums(const int* numbers, size_t count) {
    if (numbers == NULL || count == 0) {
        return NULL;
    }
    
    int* sums = (int*)malloc(count * sizeof(int));
    if (sums == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < count; i++) {
        sums[i] = sum_of_digits(numbers[i]);
    }
    
    return sums;
}

int main(void) {
    int numbers[] = {123, -456, 7890, 0, 42};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    
    int* digit_sums = compute_digit_sums(numbers, count);
    
    if (digit_sums == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        return 1;
    }
    
    for (size_t i = 0; i < count; i++) {
        printf("Number: %d, Digit Sum: %d\n", numbers[i], digit_sums[i]);
    }
    
    free(digit_sums);
    
    return 0;
}