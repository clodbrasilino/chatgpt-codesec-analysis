#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define INPUT_SIZE 256

long long sum_prime_divisors(long long n) {
    long long sum = 0;
    long long temp;
    
    if (n == LLONG_MIN) {
        temp = LLONG_MAX;
    } else {
        temp = (n < 0) ? -n : n;
    }
    
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
    char *input = NULL;
    char *endptr;
    long long number;
    size_t len;
    size_t capacity = INPUT_SIZE;
    /* Possible weaknesses found:
     *  Variable 'size' is assigned a value that is never used. [unreadVariable]
     */
    size_t size = 0;
    
    printf("Enter a number: ");
    
    input = malloc(capacity);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    if (fgets(input, capacity, stdin) == NULL) {
        free(input);
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        free(input);
        fprintf(stderr, "Invalid input: empty string\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    number = strtoll(input, &endptr, 10);
    
    if (errno == ERANGE) {
        free(input);
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input) {
        free(input);
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }
    
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    
    if (*endptr != '\0') {
        free(input);
        fprintf(stderr, "Invalid input: trailing characters\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of prime divisors: %lld\n", sum_prime_divisors(number));
    
    free(input);
    return EXIT_SUCCESS;
}