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
        for (size_t count = counts[(size_t)digit]; count != 0; --count) {
            result[position++] = (char)('0' + digit);
        }
    }

    result[position] = '\0';
    return result;
}

static int read_digits(char **digits, size_t *length)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[MAX_DIGITS + 3];
    size_t used = 0;
    char *buffer;
    int terminated = 0;

    if (digits == NULL || length == NULL) {
        errno = EINVAL;
        return -1;
    }

    *digits = NULL;
    *length = 0;

    if (fgets(line, sizeof line, stdin) == NULL) {
        errno = ferror(stdin) ? EIO : EINVAL;
        return -1;
    }

    while (line[used] != '\0') {
        if (line[used] == '\n') {
            terminated = 1;
            break;
        }

        if (line[used] == '\r') {
            if (line[used + 1] == '\n') {
                ++used;
            }
            terminated = 1;
            break;
        }

        if (line[used] < '0' || line[used] > '9') {
            errno = EINVAL;
            return -1;
        }

        ++used;
    }

    if (!terminated) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != EOF) {
            do {
                if (ch == '\n') {
                    break;
                }

                if (ch == '\r') {
                    /* Possible weaknesses found:
                     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    int next = fgetc(stdin);

                    if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
                        errno = EIO;
                        return -1;
                    }

                    if (next == EOF && ferror(stdin)) {
                        errno = EIO;
                        return -1;
                    }

                    break;
                }

                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF);

            if (ch == EOF && ferror(stdin)) {
                errno = EIO;
                return -1;
            }

            errno = EOVERFLOW;
            return -1;
        }

        if (ferror(stdin)) {
            errno = EIO;
            return -1;
        }
    }

    if (used == 0) {
        errno = EINVAL;
        return -1;
    }

    if (used > MAX_DIGITS) {
        errno = EOVERFLOW;
        return -1;
    }

    buffer = malloc(used + 1);
    if (buffer == NULL) {
        errno = ENOMEM;
        return -1;
    }

    for (size_t i = 0; i < used; ++i) {
        buffer[i] = line[i];
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