#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

static void discard_remaining_input(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

int binary_to_decimal(const char *binary, long *result) {
    if (binary == NULL || result == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (*binary == '\0') {
        errno = EINVAL;
        return -1;
    }

    long decimal = 0;
    size_t length = 0;
    
    while (binary[length] != '\0') {
        length++;
        if (length > (size_t)(sizeof(long) * CHAR_BIT)) {
            break;
        }
    }
    
    if (length > (size_t)(sizeof(long) * CHAR_BIT)) {
        errno = ERANGE;
        return -1;
    }

    const char *p = binary;
    while (*p != '\0') {
        if (*p != '0' && *p != '1') {
            errno = EINVAL;
            return -1;
        }

        if (decimal > (LONG_MAX - (*p - '0')) / 2) {
            errno = ERANGE;
            return -1;
        }

        decimal = decimal * 2 + (*p - '0');
        p++;
    }

    *result = decimal;
    return 0;
}

int main(void) {
    char input[BUFFER_SIZE + 2];
    long result;
    size_t len;
    int is_overflow;

    memset(input, 0, sizeof(input));

    printf("Enter a binary number: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            perror("Input error");
            return 1;
        }
        fprintf(stderr, "No input provided\n");
        return 1;
    }

    len = strlen(input);
    is_overflow = (len > 0 && input[len - 1] != '\n' && len >= (size_t)(sizeof(input) - 1));

    if (is_overflow) {
        discard_remaining_input();
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    else if (is_overflow && len >= (size_t)(sizeof(input) - 1)) {
        input[sizeof(input) - 2] = '\0';
        len = sizeof(input) - 2;
    }

    if (len == 0) {
        fprintf(stderr, "No input provided\n");
        return 1;
    }

    if (binary_to_decimal(input, &result) != 0) {
        switch (errno) {
            case EINVAL:
                fprintf(stderr, "Invalid input: please provide a valid binary number\n");
                break;
            case ERANGE:
                fprintf(stderr, "Error: result exceeds range of long\n");
                break;
            default:
                fprintf(stderr, "Unexpected error occurred\n");
                break;
        }
        return 1;
    }

    printf("Decimal equivalent: %ld\n", result);

    return 0;
}