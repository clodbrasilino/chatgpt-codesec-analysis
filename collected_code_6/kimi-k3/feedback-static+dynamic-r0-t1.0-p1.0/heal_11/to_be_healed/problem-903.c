#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long count_unset_bits(unsigned int n)
{
    unsigned long long total_unset = 0;
    unsigned int i;
    
    for (i = 1; i <= n; i++) {
        unsigned int num = i;
        unsigned int bits = 0;
        unsigned int set_bits = 0;
        
        while (num > 0) {
            if ((num & 1U) == 1U) {
                set_bits++;
            }
            bits++;
            num >>= 1;
        }
        
        if (bits == 0) {
            bits = 1;
        }
        
        total_unset += (unsigned long long)(bits - set_bits);
    }
    
    return total_unset;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *endptr;
    long val;
    unsigned int n;
    unsigned long long result;
    size_t len;
    int truncated;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = 0;
    truncated = 1;
    
    while (len < sizeof(input)) {
        if (input[len] == '\0') {
            truncated = 0;
            break;
        }
        if (input[len] == '\n') {
            input[len] = '\0';
            truncated = 0;
            break;
        }
        len++;
    }
    
    if (truncated) {
        int c;
        input[sizeof(input) - 1] = '\0';
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    errno = 0;
    val = strtol(input, &endptr, 10);
    
    if (errno != 0 || endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (val < 1 || val > UINT_MAX) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }
    
    n = (unsigned int)val;
    result = count_unset_bits(n);
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}