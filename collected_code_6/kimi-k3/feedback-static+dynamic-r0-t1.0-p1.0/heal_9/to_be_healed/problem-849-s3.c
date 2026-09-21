#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

long long sum_prime_divisors(long long n) {
    long long sum = 0;
    long long temp = (n < 0) ? -n : n;
    
    if (temp < 2) {
        return 0;
    }
    
    if (temp % 2 == 0) {
        sum += 2;
        while (temp % 2 == 0) {
            temp /= 2;
        }
    }
    
    for (long long i = 3; i <= temp / i; i += 2) {
        if (temp % i == 0) {
            sum += i;
            while (temp % i == 0) {
                temp /= i;
            }
        }
    }
    
    if (temp > 1) {
        sum += temp;
    }
    
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *endptr;
    long long number;
    size_t len;
    size_t input_size = sizeof(input);
    
    printf("Enter a number: ");
    
    if (fgets(input, input_size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    input[input_size - 1] = '\0';
    
    len = strnlen(input, input_size);
    
    if (len == input_size - 1 && input[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    errno = 0;
    number = strtoll(input, &endptr, 10);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input) {
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n') {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of prime divisors: %lld\n", sum_prime_divisors(number));
    
    return EXIT_SUCCESS;
}