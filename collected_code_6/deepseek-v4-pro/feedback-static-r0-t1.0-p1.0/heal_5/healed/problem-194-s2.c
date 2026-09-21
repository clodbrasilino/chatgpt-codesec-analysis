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

static int is_whitespace(int c) {
    return c == ' ' || c == '\t';
}

static void discard_input_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static size_t trim_leading_whitespace(char *str, size_t len) {
    size_t start = 0;
    while (start < len && is_whitespace((unsigned char)str[start])) {
        start++;
    }
    if (start > 0 && start < len) {
        memmove(str, str + start, len - start + 1);
    } else if (start > 0) {
        str[0] = '\0';
        return 0;
    }
    return len - start;
}

static size_t trim_trailing_whitespace(char *str, size_t len) {
    while (len > 0 && is_whitespace((unsigned char)str[len - 1])) {
        len--;
        str[len] = '\0';
    }
    return len;
}

int main(void) {
    char input[256];
    long decimal_value;

    printf("Enter an octal number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    size_t input_len = strnlen(input, sizeof(input));
    if (input_len > 0 && input[input_len - 1] != '\n' && input_len >= sizeof(input) - 1) {
        discard_input_line();
        fprintf(stderr, "Input too long\n");
        return 1;
    }

    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }

    input_len = trim_leading_whitespace(input, input_len);
    input_len = trim_trailing_whitespace(input, input_len);

    if (input_len == 0 || input[0] == '\0') {
        fprintf(stderr, "Invalid octal number\n");
        return 1;
    }

    if (octal_to_decimal(input, &decimal_value) != 0) {
        fprintf(stderr, "Invalid octal number\n");
        return 1;
    }

    printf("Decimal equivalent: %ld\n", decimal_value);
    return 0;
}