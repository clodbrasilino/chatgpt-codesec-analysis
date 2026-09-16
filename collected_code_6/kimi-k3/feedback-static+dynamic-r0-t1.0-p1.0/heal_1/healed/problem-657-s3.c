#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int find_first_digit_factorial(unsigned int n)
{
    double log_sum = 0.0;
    unsigned int i;
    double fractional;
    int first_digit;
    
    if (n == 0 || n == 1) {
        return 1;
    }
    
    for (i = 2; i <= n; i++) {
        log_sum += log10((double)i);
    }
    
    fractional = log_sum - floor(log_sum);
    first_digit = (int)pow(10.0, fractional);
    
    return first_digit;
}

int main(void)
{
    unsigned int num;
    int result;
    int scan_result;
    
    printf("Enter a non-negative integer: ");
    scan_result = scanf("%u", &num);
    
    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (num > 100000) {
        fprintf(stderr, "Error: Number too large (max 100000)\n");
        return EXIT_FAILURE;
    }
    
    result = find_first_digit_factorial(num);
    
    if (result < 1 || result > 9) {
        fprintf(stderr, "Error: Computation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("First digit of %u! is: %d\n", num, result);
    
    return EXIT_SUCCESS;
}