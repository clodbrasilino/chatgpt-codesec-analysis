#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

static int octal_to_decimal(const char *octal_str, long *result) {
    char *endptr;

    if (octal_str == NULL || result == NULL) {
        return -1;
    }

    while (*octal_str == ' ' || *octal_str == '\t') {
        octal_str++;
    }

    if (*octal_str == '\0') {
        return -1;
    }

    errno = 0;
    long value = strtol(octal_str, &endptr, 8);

    if (errno == ERANGE) {
        return -1;
    }

    if (endptr == octal_str) {
        return -1;
    }

    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }

    if (*endptr != '\0') {
        return -1;
    }

    *result = value;
    return 0;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    long decimal_value;

    printf("Enter an octal number: ");
    
    ssize_t line_len = getline(&input, &input_size, stdin);
    if (line_len == -1) {
        free(input);
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    if (line_len > 0 && input[line_len - 1] == '\n') {
        input[line_len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'line_len' is assigned a value that is never used. [unreadVariable]
         */
        line_len--;
    }

    if (octal_to_decimal(input, &decimal_value) != 0) {
        free(input);
        fprintf(stderr, "Invalid octal number\n");
        return 1;
    }

    printf("Decimal equivalent: %ld\n", decimal_value);
    free(input);
    return 0;
}