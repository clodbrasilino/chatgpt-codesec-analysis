#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum ReadStatus {
    READ_OK,
    READ_END,
    READ_ERROR,
    READ_NO_MEMORY
};

static enum ReadStatus read_string(FILE *stream, char **result)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    int ch;

    if (stream == NULL || result == NULL) {
        return READ_ERROR;
    }

    *result = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return ferror(stream) ? READ_ERROR : READ_END;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return READ_NO_MEMORY;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return READ_NO_MEMORY;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return READ_NO_MEMORY;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    }

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return READ_ERROR;
    }

    buffer[length] = '\0';
    *result = buffer;
    return READ_OK;
}

static bool minimum_swaps(const char *source,
                          const char *target,
                          size_t *swaps)
{
    size_t zero_to_one = 0;
    size_t one_to_zero = 0;
    size_t i = 0;

    if (source == NULL || target == NULL || swaps == NULL) {
        return false;
    }

    while (source[i] != '\0' && target[i] != '\0') {
        if ((source[i] != '0' && source[i] != '1') ||
            (target[i] != '0' && target[i] != '1')) {
            return false;
        }

        if (source[i] == '0' && target[i] == '1') {
            ++zero_to_one;
        } else if (source[i] == '1' && target[i] == '0') {
            ++one_to_zero;
        }

        ++i;
    }

    if (source[i] != '\0' || target[i] != '\0') {
        return false;
    }

    if (zero_to_one != one_to_zero) {
        return false;
    }

    *swaps = zero_to_one;
    return true;
}

int main(void)
{
    char *source = NULL;
    char *target = NULL;
    size_t swaps = 0;
    enum ReadStatus status;

    status = read_string(stdin, &source);
    if (status != READ_OK) {
        fputs("Failed to read the source string.\n", stderr);
        return EXIT_FAILURE;
    }

    status = read_string(stdin, &target);
    if (status != READ_OK) {
        free(source);
        fputs("Failed to read the target string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!minimum_swaps(source, target, &swaps)) {
        free(target);
        free(source);

        if (puts("-1") == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    free(target);
    free(source);

    if (printf("%zu\n", swaps) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}