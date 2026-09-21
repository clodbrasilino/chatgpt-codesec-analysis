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

    size_t input_len = strnlen(input, sizeof(input));
    if (input_len == sizeof(input) && input[input_len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return 1;
    }

    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }

    size_t start = 0;
    while (start < input_len && (input[start] == ' ' || input[start] == '\t')) {
        start++;
    }
    if (start > 0) {
        size_t remaining = input_len - start;
        memmove(input, input + start, remaining + 1);
        input_len = remaining;
    }
    
    size_t end = input_len;
    while (end > 0 && (input[end - 1] == ' ' || input[end - 1] == '\t')) {
        end--;
        input[end] = '\0';
    }

    if (octal_to_decimal(input, &decimal_value) != 0) {
        fprintf(stderr, "Invalid octal number\n");
        return 1;
    }

    printf("Decimal equivalent: %ld\n", decimal_value);
    return 0;
}