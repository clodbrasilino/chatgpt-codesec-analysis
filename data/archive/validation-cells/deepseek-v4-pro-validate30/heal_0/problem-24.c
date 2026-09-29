#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

long long binary_to_decimal(const char *binary_str) {
    if (binary_str == NULL || *binary_str == '\0') {
        errno = EINVAL;
        return 0;
    }

    size_t len = strlen(binary_str);
    if (len > 63) {
        errno = ERANGE;
        return 0;
    }

    long long result = 0;
    for (size_t i = 0; i < len; i++) {
        if (binary_str[i] != '0' && binary_str[i] != '1') {
            errno = EINVAL;
            return 0;
        }
        result = (result << 1) | (binary_str[i] - '0');
        if (result < 0) {
            errno = ERANGE;
            return 0;
        }
    }

    return result;
}

int main(void) {
    char input[128];
    char *newline_pos;

    printf("Enter a binary number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    newline_pos = strchr(input, '\n');
    if (newline_pos != NULL) {
        *newline_pos = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    errno = 0;
    long long decimal = binary_to_decimal(input);

    if (errno != 0) {
        if (errno == EINVAL) {
            fprintf(stderr, "Invalid binary number\n");
        } else if (errno == ERANGE) {
            fprintf(stderr, "Binary number out of range\n");
        } else {
            fprintf(stderr, "Conversion error\n");
        }
        return 1;
    }

    printf("Decimal equivalent: %lld\n", decimal);
    return 0;
}