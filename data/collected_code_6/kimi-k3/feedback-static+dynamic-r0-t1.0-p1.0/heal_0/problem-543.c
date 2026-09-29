#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int count_digits(long long number)
{
    int count = 0;
    
    if (number == 0) {
        return 1;
    }
    
    if (number < 0) {
        if (number == LLONG_MIN) {
            number = LLONG_MAX;
        } else {
            number = -number;
        }
    }
    
    while (number != 0) {
        number /= 10;
        count++;
    }
    
    return count;
}

int main(void)
{
    long long num1 = 0;
    long long num2 = 0;
    long long sum = 0;
    int digit_count = 0;
    
    printf("Enter two numbers: ");
    
    if (scanf("%lld %lld", &num1, &num2) != 2) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if ((num2 > 0 && num1 > LLONG_MAX - num2) ||
        (num2 < 0 && num1 < LLONG_MIN - num2)) {
        fprintf(stderr, "Error: Integer overflow\n");
        return EXIT_FAILURE;
    }
    
    sum = num1 + num2;
    digit_count = count_digits(sum);
    
    printf("Sum: %lld\n", sum);
    printf("Number of digits: %d\n", digit_count);
    
    return EXIT_SUCCESS;
}