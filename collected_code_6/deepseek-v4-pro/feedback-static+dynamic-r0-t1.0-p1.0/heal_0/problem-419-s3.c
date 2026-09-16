#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int round_numbers_and_sum(const double *numbers, size_t length) {
    int total_sum = 0;
    for (size_t i = 0; i < length; i++) {
        total_sum += (int)round(numbers[i]);
    }
    return total_sum;
}

int main(void) {
    double numbers[] = {1.4, 2.6, 3.5, 4.2, 5.8};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    
    int sum = round_numbers_and_sum(numbers, length);
    int result = sum * (int)length;
    
    printf("%d\n", result);
    
    return 0;
}