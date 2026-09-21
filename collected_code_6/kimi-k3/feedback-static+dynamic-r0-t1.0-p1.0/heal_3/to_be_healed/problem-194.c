#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

int octal_to_decimal(const char *octal_str, long *result) {
    char *endptr;
    long value;
    
    if (octal_str == NULL || result == NULL) {
        return -1;
    }
    
    if (*octal_str == '\0') {
        return -1;
    }
    
    errno = 0;
    value = strtol(octal_str, &endptr, 8);
    
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
        return -1;
    }
    
    if (endptr == octal_str || *endptr != '\0') {
        return -1;
    }
    
    *result = value;
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    long decimal;
    
    printf("Enter an octal number: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    
    if (octal_to_decimal(input, &decimal) != 0) {
        fprintf(stderr, "Invalid octal number\n");
        return EXIT_FAILURE;
    }
    
    printf("Decimal: %ld\n", decimal);
    
    return EXIT_SUCCESS;
}