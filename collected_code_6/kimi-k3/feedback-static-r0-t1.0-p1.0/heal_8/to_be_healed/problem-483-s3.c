#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

bool is_factorial_divisible(uint64_t n, uint64_t x) {
    if (x == 0) {
        return false;
    }
    
    uint64_t factorial = 1;
    uint64_t i;
    
    for (i = 1; i <= n; i++) {
        if (factorial > UINT64_MAX / i) {
            factorial = 0;
            break;
        }
        factorial *= i;
        if (factorial % x == 0) {
            return true;
        }
    }
    
    if (factorial == 0 && x != 1) {
        return true;
    }
    
    return false;
}

uint64_t find_first_natural_number(uint64_t x) {
    if (x == 0) {
        return 0;
    }
    if (x == 1) {
        return 1;
    }
    
    uint64_t n = 1;
    
    while (n < UINT64_MAX) {
        if (is_factorial_divisible(n, x)) {
            return n;
        }
        n++;
    }
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    uint64_t x;
    char *endptr;
    size_t len;
    
    printf("Enter the value of x: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0 || len >= sizeof(buffer) - 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    errno = 0;
    x = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || *endptr != '\0' || endptr != buffer + len) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    uint64_t result = find_first_natural_number(x);
    
    if (result == 0 && x != 0) {
        fprintf(stderr, "No solution found\n");
        return 1;
    }
    
    printf("The first natural number whose factorial is divisible by %" PRIu64 " is %" PRIu64 ".\n", x, result);
    
    return 0;
}