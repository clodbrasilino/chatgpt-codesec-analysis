#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

int count_odd_set_bits(int n)
{
    int count = 0;
    int i;
    
    if (n < 0) {
        return -1;
    }
    
    for (i = 0; i <= n; i++) {
        int bits = 0;
        int temp = i;
        while (temp > 0) {
            bits += temp & 1;
            temp >>= 1;
        }
        if (bits % 2 != 0) {
            count++;
        }
    }
    
    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *endptr;
    long val;
    int n;
    int result;
    size_t len;
    
    printf("Enter a non-negative integer: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(input, &endptr, 10);
    
    if (errno != 0) {
        fprintf(stderr, "Error during conversion\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input) {
        fprintf(stderr, "No digits were found\n");
        return EXIT_FAILURE;
    }
    
    if (*endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Invalid characters after number\n");
        return EXIT_FAILURE;
    }
    
    if (val < 0 || val > INT_MAX) {
        fprintf(stderr, "Number out of valid range\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    result = count_odd_set_bits(n);
    
    if (result < 0) {
        fprintf(stderr, "Error in calculation\n");
        return EXIT_FAILURE;
    }
    
    printf("Number of integers from 0 to %d with odd number of set bits: %d\n", n, result);
    
    return EXIT_SUCCESS;
}