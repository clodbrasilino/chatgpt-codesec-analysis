#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

double harmonic_sum(int n)
{
    double sum = 0.0;
    int i;
    
    if (n <= 0) {
        return 0.0;
    }
    
    for (i = 1; i <= n; i++) {
        sum += 1.0 / (double)i;
    }
    
    return sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    long value;
    int n;
    double result;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer) && buffer[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    value = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    n = (int)value;
    
    if (n < 1) {
        fprintf(stderr, "n must be at least 1\n");
        return EXIT_FAILURE;
    }
    
    result = harmonic_sum(n);
    
    printf("%.15f\n", result);
    
    return EXIT_SUCCESS;
}