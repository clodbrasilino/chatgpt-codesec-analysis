#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long nonagonal_number(int n) {
    if (n < 0 || n > 1851276) {
        return -1;
    }
    return (long long)n * (7LL * n - 5) / 2;
}

int main(void) {
    int n;
    char buffer[256];
    char *endptr;
    long val;
    long long result;

    printf("Enter the value of n: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || val > 1851276 || val < 0) {
        fprintf(stderr, "Invalid input: out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        return EXIT_FAILURE;
    }

    n = (int)val;
    result = nonagonal_number(n);
    
    if (result == -1) {
        fprintf(stderr, "Error: input too large, would cause overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("Nonagonal number for n=%d is %lld\n", n, result);
    
    return EXIT_SUCCESS;
}