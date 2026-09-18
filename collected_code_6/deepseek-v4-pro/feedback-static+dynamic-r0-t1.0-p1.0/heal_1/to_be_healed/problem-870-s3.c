#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 50, got 0
  *  test case 0 failed: expected 48, got 0
  *  test case 2 failed: expected 522, got 0
  */

double sum_positive_numbers(const double *numbers, size_t count) {
    double sum = 0.0;
    size_t i;
    
    if (numbers == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to sum_positive_numbers\n");
        exit(EXIT_FAILURE);
    }
    
    for (i = 0; i < count; i++) {
        if (numbers[i] > 0.0) {
            sum += numbers[i];
        }
    }
    
    return sum;
}

int main(void) {
    double numbers[] = {1.5, -2.0, 3.7, 0.0, 4.2, -1.1, 5.9};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    double result;
    
    result = sum_positive_numbers(numbers, count);
    
    printf("Sum of positive numbers: %.2f\n", result);
    
    return 0;
}