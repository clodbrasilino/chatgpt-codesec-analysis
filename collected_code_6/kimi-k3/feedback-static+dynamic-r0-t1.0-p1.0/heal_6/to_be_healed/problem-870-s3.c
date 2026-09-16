#include <stdio.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 48, got 0
  *  test case 1 failed: expected 50, got 0
  *  test case 2 failed: expected 522, got 0
  */

double sum_positive(const double numbers[], size_t count) {
    double sum = 0.0;
    size_t i;
    
    if (numbers == NULL) {
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
    double test0[] = {1.5, -2.0, 3.7, -4.2, 5.0, 0.0, -1.0, 10.5};
    double test1[] = {10.0, 20.0, -5.0, 30.0, -10.0, 40.0};
    double test2[] = {100.0, 200.0, -50.0, 300.0, -100.0, 22.0};
    
    printf("%.0f\n", sum_positive(test0, sizeof(test0) / sizeof(test0[0])));
    printf("%.0f\n", sum_positive(test1, sizeof(test1) / sizeof(test1[0])));
    printf("%.0f\n", sum_positive(test2, sizeof(test2) / sizeof(test2[0])));
    
    return 0;
}