#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

long long cube_sum_even(int n) {
    long long sum = 0;
    long long i;
    
    for (i = 1; i <= n; i++) {
        long long even_num = 2 * i;
        sum += even_num * even_num * even_num;
    }
    
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    long val;
    int n;
    long long result;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    
    if (len == 0) {
        fprintf(stderr, "Invalid input: empty input\n");
        return EXIT_FAILURE;
    }
    
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        fprintf(stderr, "Invalid input: input too long\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < 0) {
        fprintf(stderr, "Invalid input: out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer) {
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }
    
    if (*endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    result = cube_sum_even(n);
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}