#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

int octal_to_decimal(const char *octal_str, long *result) {
    if (octal_str == NULL || result == NULL) {
        return -1;
    }

    if (*octal_str == '\0') {
        return -1;
    }

    const char *p = octal_str;
    
    if (*p == '+' || *p == '-') {
        p++;
    }
    
    if (*p == '\0') {
        return -1;
    }

    for (const char *q = p; *q != '\0'; q++) {
        if (*q < '0' || *q > '7') {
            return -1;
        }
    }

    errno = 0;
    char *endptr;
    long value = strtol(octal_str, &endptr, 8);

    if (errno == ERANGE) {
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
    char input[256];
    long decimal_value;

    printf("Enter an octal number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    size_t leading = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    while (leading < strlen(input) && (input[leading] == ' ' || input[leading] == '\t')) {
        leading++;
    }
    if (leading > 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(input, input + leading, strlen(input + leading) + 1);
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    while (len > 0 && (input[len - 1] == ' ' || input[len - 1] == '\t')) {
        input[len - 1] = '\0';
        len--;
    }

    if (octal_to_decimal(input, &decimal_value) != 0) {
        fprintf(stderr, "Invalid octal number\n");
        return 1;
    }

    printf("Decimal equivalent: %ld\n", decimal_value);
    return 0;
}