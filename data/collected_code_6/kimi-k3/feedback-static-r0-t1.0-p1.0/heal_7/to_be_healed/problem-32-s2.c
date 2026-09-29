#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

uint64_t largest_prime_factor(uint64_t n) {
    uint64_t largest = 0;
    
    if (n < 2) {
        return 0;
    }
    
    while (n % 2 == 0) {
        largest = 2;
        n /= 2;
    }
    
    for (uint64_t i = 3; i <= n / i; i += 2) {
        while (n % i == 0) {
            largest = i;
            n /= i;
        }
    }
    
    if (n > 1) {
        largest = n;
    }
    
    return largest;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    char *endptr;
    unsigned long long num;
    int valid = 1;
    
    printf("Enter a positive integer: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    if (buffer[0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        if (!isdigit((unsigned char)buffer[i])) {
            valid = 0;
            break;
        }
    }
    
    if (!valid) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    errno = 0;
    num = strtoull(buffer, &endptr, 10);
    
    if (errno == ERANGE || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (num > UINT64_MAX) {
        fprintf(stderr, "Number too large\n");
        return 1;
    }
    
    uint64_t result = largest_prime_factor((uint64_t)num);
    
    if (result == 0) {
        printf("No prime factors exist for numbers less than 2\n");
    } else {
        printf("Largest prime factor: %" PRIu64 "\n", result);
    }
    
    return 0;
}