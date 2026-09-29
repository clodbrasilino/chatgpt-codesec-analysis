#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 34

int octal_to_decimal(const char *octal_str, long *result) {
    if (octal_str == NULL || result == NULL || *octal_str == '\0') {
        return -1;
    }
    
    const char *p = octal_str;
    if (*p == '+' || *p == '-') {
        p++;
        if (*p == '\0') {
            return -1;
        }
    }
    
    for (const char *q = p; *q != '\0'; q++) {
        if (*q < '0' || *q > '7') {
            return -1;
        }
    }
    
    errno = 0;
    char *endptr;
    long value = strtol(octal_str, &endptr, 8);
    
    if (errno == ERANGE || endptr == octal_str || *endptr != '\0') {
        return -1;
    }
    
    *result = value;
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_SIZE] = {0};
    long decimal;
    
    printf("Enter an octal number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    /* Possible weaknesses found:
     *  The scope of the variable 'buffer_exceeded' can be reduced. [variableScope]
     *  Variable 'buffer_exceeded' is assigned a value that is never used. [unreadVariable]
     */
    int buffer_exceeded = 0;
    int has_newline = 0;
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        has_newline = 1;
        len--;
    }
    
    if (!has_newline && len == sizeof(input) - 1) {
        /* Possible weaknesses found:
         *  Value stored to 'buffer_exceeded' is never read [deadcode.DeadStores]
         *  Variable 'buffer_exceeded' is assigned a value that is never used. [unreadVariable]
         */
        buffer_exceeded = 1;
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) { }
        /* Possible weaknesses found:
         *  Variable 'input[sizeof(input)-1]' is assigned a value that is never used. [unreadVariable]
         */
        input[sizeof(input) - 1] = '\0';
        fprintf(stderr, "Input too long\n");
        return 1;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid octal number\n");
        return 1;
    }
    
    if (octal_to_decimal(input, &decimal) != 0) {
        fprintf(stderr, "Invalid octal number\n");
        return 1;
    }
    
    printf("Decimal equivalent: %ld\n", decimal);
    
    return 0;
}