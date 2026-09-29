#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'strlen'
 */
#include <stdint.h>

unsigned long long sum_of_squares_even(int n) {
    unsigned long long sum = 0;
    int i;
    for (i = 1; i <= n; i++) {
        unsigned long long even_num = 2ULL * (unsigned int)i;
        sum += even_num * even_num;
    }
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    char *endptr;
    long val;
    int n;
    unsigned long long result;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < 0) {
        fprintf(stderr, "Invalid input: out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        return EXIT_FAILURE;
    }

    n = (int)val;
    result = sum_of_squares_even(n);
    
    if (printf("%llu\n", result) < 0) {
        fprintf(stderr, "Error writing output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}