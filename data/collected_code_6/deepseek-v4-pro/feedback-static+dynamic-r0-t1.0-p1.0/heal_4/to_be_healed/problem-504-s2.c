#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

unsigned long long cube_sum_natural_numbers(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long sum = 0;
    unsigned long long nn = (unsigned long long)n;
    unsigned long long temp1, temp2;
    
    temp1 = nn * nn;
    temp2 = (nn + 1) * (nn + 1);
    
    if (nn > ULLONG_MAX / (nn * nn) || 
        temp1 > ULLONG_MAX / temp2) {
        return 0;
    }
    
    sum = (temp1 * temp2) / 4;
    
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[65];
    char *endptr;
    long long_val;
    size_t len;
    
    printf("Enter a positive integer: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = 0;
    int has_newline = 0;
    while (len < sizeof(input) && input[len] != '\0') {
        if (input[len] == '\n') {
            has_newline = 1;
            break;
        }
        len++;
    }
    
    if (len >= sizeof(input)) {
        fprintf(stderr, "Input too long or not null-terminated\n");
        return EXIT_FAILURE;
    }
    
    if (has_newline) {
        input[len] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) { }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    long_val = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || long_val < 0 || long_val > INT_MAX) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = cube_sum_natural_numbers((int)long_val);
    printf("Cube sum of first %d natural numbers: %llu\n", (int)long_val, result);
    
    return EXIT_SUCCESS;
}