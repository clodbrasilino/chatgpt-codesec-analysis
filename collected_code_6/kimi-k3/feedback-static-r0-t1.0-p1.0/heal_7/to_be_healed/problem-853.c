#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

long long sum_odd_factors(long long n) {
    long long sum = 0;
    long long i;
    
    if (n <= 0) {
        return 0;
    }
    
    for (i = 1; i <= n / i; i += 2) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    
    return sum;
}

int main(void) {
    long long number;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    size_t len;
    int c;
    int input_too_long = 0;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
            input_too_long = 1;
        }
        if (input_too_long || c == EOF) {
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    }
    
    errno = 0;
    number = strtoll(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (number <= 0) {
        fprintf(stderr, "Number must be positive\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", sum_odd_factors(number));
    
    return EXIT_SUCCESS;
}