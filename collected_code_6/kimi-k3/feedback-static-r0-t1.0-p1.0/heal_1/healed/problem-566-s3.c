#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned int get_sum(unsigned int n)
{
    unsigned int sum = 0;
    
    if (n == 0) {
        return 0;
    }
    
    while (n > 0) {
        unsigned int digit = n % 10;
        if (sum > UINT_MAX - digit) {
            errno = ERANGE;
            return 0;
        }
        sum += digit;
        n /= 10;
    }
    
    return sum;
}

int main(void)
{
    unsigned int num = 12345;
    unsigned int result;
    
    errno = 0;
    result = get_sum(num);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Error: Integer overflow occurred\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of digits: %u\n", result);
    
    return EXIT_SUCCESS;
}