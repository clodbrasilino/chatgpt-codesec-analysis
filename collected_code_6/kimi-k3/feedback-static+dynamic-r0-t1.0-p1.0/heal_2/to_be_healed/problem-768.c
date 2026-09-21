#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int check_odd_parity(unsigned int num)
{
    int parity = 0;
    
    while (num != 0U) {
        parity ^= 1;
        num &= (num - 1U);
    }
    
    return parity;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    unsigned long value;
    unsigned int num;
    int result;
    size_t len;
    
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
    }
    
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\0' && buffer[len - 1] != '\n') {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    value = strtoul(buffer, &endptr, 10);
    
    if (errno != 0) {
        fprintf(stderr, "Error converting input\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer) {
        fprintf(stderr, "No digits found\n");
        return EXIT_FAILURE;
    }
    
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Invalid characters in input\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }
    
    if (value > UINT_MAX) {
        fprintf(stderr, "Value out of range\n");
        return EXIT_FAILURE;
    }
    
    num = (unsigned int)value;
    result = check_odd_parity(num);
    
    if (result == 1) {
        printf("Number %u has odd parity\n", num);
    } else {
        printf("Number %u has even parity\n", num);
    }
    
    return EXIT_SUCCESS;
}