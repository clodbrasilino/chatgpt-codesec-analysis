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
        return 0.0;
    }
    
    if (count == 0) {
        return 0.0;
    }
    
    for (i = 0; i < count; i++) {
        if (numbers[i] > 0.0) {
            sum += numbers[i];
        }
    }
    
    return sum;
}

int main(void) {
    double test1[] = {1.5, -2.0, 3.7, 0.0, 4.2, -1.1, 5.9};
    size_t count1 = sizeof(test1) / sizeof(test1[0]);
    double result1 = sum_positive_numbers(test1, count1);
    printf("%.0f\n", result1);
    
    double test2[] = {10.0, 20.0, -5.0, 0.0, 15.0, -3.0, 8.0};
    size_t count2 = sizeof(test2) / sizeof(test2[0]);
    double result2 = sum_positive_numbers(test2, count2);
    printf("%.0f\n", result2);
    
    double test3[] = {100.0, 200.0, -50.0, 0.0, 150.0, -30.0, 80.0, -10.0, 72.0};
    size_t count3 = sizeof(test3) / sizeof(test3[0]);
    double result3 = sum_positive_numbers(test3, count3);
    printf("%.0f\n", result3);
    
    return 0;
}