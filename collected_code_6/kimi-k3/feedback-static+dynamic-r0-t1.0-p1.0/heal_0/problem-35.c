#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>

int64_t rectangular_number(uint64_t n, int *err)
{
    if (n == 0 || n > UINT32_MAX) {
        *err = ERANGE;
        return 0;
    }
    
    *err = 0;
    return (int64_t)(n * (n + 1));
}

int main(void)
{
    uint64_t n;
    int err;
    int64_t result;
    
    printf("Enter n: ");
    
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = rectangular_number(n, &err);
    
    if (err != 0) {
        fprintf(stderr, "Error: n out of valid range\n");
        return EXIT_FAILURE;
    }
    
    printf("Rectangular number: %lld\n", result);
    
    return EXIT_SUCCESS;
}