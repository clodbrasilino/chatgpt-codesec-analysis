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
        continue;
    }
    if (ch == EOF) {
        clearerr(stdin);
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
    char *input = NULL;
    size_t bufsize = 0;
    long result;
    ssize_t len;

    printf("Enter a binary number: ");

    len = getline(&input, &bufsize, stdin);
    if (len == -1) {
        free(input);
        if (ferror(stdin)) {
            perror("Input error");
            return 1;
        }
        fprintf(stderr, "No input provided\n");
        return 1;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        discard_remaining_input();
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
        free(input);
        return 1;
    }

    printf("Decimal equivalent: %ld\n", result);

    free(input);
    return 0;
}