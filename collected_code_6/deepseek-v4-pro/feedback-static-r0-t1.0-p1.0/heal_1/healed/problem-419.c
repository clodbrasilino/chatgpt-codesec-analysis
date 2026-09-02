#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double rounded_sum_multiplied_by_length(const double *numbers, int length) {
    if (numbers == NULL || length <= 0) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (int i = 0; i < length; i++) {
        sum += round(numbers[i]);
    }
    
    return sum * (double)length;
}

int main(void) {
    double numbers[] = {1.4, 2.6, 3.5, 4.2, 5.7};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    
    double result = rounded_sum_multiplied_by_length(numbers, length);
    printf("%.2f\n", result);
    
    return 0;
}