#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <inttypes.h>

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
    char buffer[64];
    char *endptr;
    unsigned long long temp;
    
    printf("Enter n: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    temp = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    n = (uint64_t)temp;
    
    result = rectangular_number(n, &err);
    
    if (err != 0) {
        fprintf(stderr, "Error: n out of valid range\n");
        return EXIT_FAILURE;
    }
    
    printf("Rectangular number: %" PRId64 "\n", result);
    
    return EXIT_SUCCESS;
}