#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 4095U

static char *largest_number_from_digits(const char *digits, size_t length)
{
    size_t counts[10] = {0};
    char *result;
    size_t position = 0;

    if (digits == NULL || length == 0 || length > MAX_DIGITS) {
        errno = EINVAL;
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char ch = (unsigned char)digits[i];

        if (ch < (unsigned char)'0' || ch > (unsigned char)'9') {
            errno = EINVAL;
            return NULL;
        }

        ++counts[ch - (unsigned char)'0'];
    }

    result = malloc(length + 1);
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (int digit = 9; digit >= 0; --digit) {
        size_t count = counts[(size_t)digit];

        while (count-- > 0) {
            result[position++] = (char)('0' + digit);
        }
    }

    result[position] = '\0';
    return result;
}

static int discard_remainder(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            return 0;
        }

        if (ch == '\r') {
            ch = fgetc(stdin);

            if (ch != '\n' && ch != EOF && ungetc(ch, stdin) == EOF) {
                errno = EIO;
                return -1;
            }

            if (ch == EOF && ferror(stdin)) {
                errno = EIO;
                return -1;
            }

            return 0;
        }
    }

    if (ferror(stdin)) {
        errno = EIO;
        return -1;
    }

    return 0;
}

static int read_digits(char **digits, size_t *length)
{
    char *buffer;
    size_t used = 0;
    int ch;
    int overflow = 0;
    int invalid = 0;

    if (digits == NULL || length == NULL) {
        errno = EINVAL;
        return -1;
    }

    *digits = NULL;
    *length = 0;

    buffer = malloc((size_t)MAX_DIGITS + 1);
    if (buffer == NULL) {
        errno = ENOMEM;
        return -1;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
                free(buffer);
                errno = EIO;
                return -1;
            }

            if (next == EOF && ferror(stdin)) {
                free(buffer);
                errno = EIO;
                return -1;
            }

            break;
        }

        if (used >= MAX_DIGITS) {
            overflow = 1;

            if (discard_remainder() != 0) {
                free(buffer);
                return -1;
            }

            break;
        }

        if (ch < '0' || ch > '9') {
            invalid = 1;
        } else {
            buffer[used] = (char)ch;
        }

        ++used;
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        errno = EIO;
        return -1;
    }

    if (overflow) {
        free(buffer);
        errno = EOVERFLOW;
        return -1;
    }

    if (invalid || used == 0) {
        free(buffer);
        errno = EINVAL;
        return -1;
    }

    buffer[used] = '\0';
    *digits = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *digits = NULL;
    char *largest;
    size_t length = 0;

    if (read_digits(&digits, &length) != 0) {
        switch (errno) {
        case EOVERFLOW:
            fputs("Input is too long.\n", stderr);
            break;
        case EINVAL:
            fputs("Input must contain one or more decimal digits.\n", stderr);
            break;
        case ENOMEM:
            fputs("Unable to allocate memory.\n", stderr);
            break;
        default:
            fputs("Failed to read input.\n", stderr);
            break;
        }

        return EXIT_FAILURE;
    }

    largest = largest_number_from_digits(digits, length);
    free(digits);

    if (largest == NULL) {
        if (errno == EINVAL) {
            fputs("Input must contain one or more decimal digits.\n", stderr);
        } else {
            fputs("Unable to allocate memory.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    if (puts(largest) == EOF) {
        free(largest);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(largest);

    if (fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}