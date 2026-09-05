#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>

static uint64_t sum_of_squares(uint64_t n)
{
    if (n == 0) {
        return 0;
    }
    
    if (n > 1862644) {
        errno = ERANGE;
        return UINT64_MAX;
    }
    
    return (n * (n + 1) * (2 * n + 1)) / 6;
}

int main(void)
{
    uint64_t n;
    int scan_result;
    
    printf("Enter a positive integer: ");
    scan_result = scanf("%llu", &n);
    
    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    errno = 0;
    uint64_t result = sum_of_squares(n);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Error: Input too large, result would overflow\n");
        return 1;
    }
    
    printf("Sum of squares: %llu\n", result);
    
    return 0;
}