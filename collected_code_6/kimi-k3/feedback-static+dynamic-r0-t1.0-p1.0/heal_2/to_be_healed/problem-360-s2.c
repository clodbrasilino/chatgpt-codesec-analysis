#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

uint64_t carol_number(uint64_t n) {
    if (n == 0 || n > 31) {
        return UINT64_MAX;
    }
    
    uint64_t power = 1ULL << n;
    uint64_t temp = power - 1;
    
    if (temp > UINT64_MAX / temp) {
        return UINT64_MAX;
    }
    
    return temp * temp - 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *endptr;
    unsigned long long n;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    if (input[0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    n = strtoull(input, &endptr, 10);
    
    if (errno == ERANGE || endptr == input || *endptr != '\0' || n > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    uint64_t result = carol_number((uint64_t)n);
    
    if (result == UINT64_MAX) {
        if (n == 0 || n > 31) {
            fprintf(stderr, "Input out of valid range\n");
        } else {
            fprintf(stderr, "Overflow occurred\n");
        }
        return EXIT_FAILURE;
    }
    
    printf("%" PRIu64 "\n", result);
    
    return EXIT_SUCCESS;
}