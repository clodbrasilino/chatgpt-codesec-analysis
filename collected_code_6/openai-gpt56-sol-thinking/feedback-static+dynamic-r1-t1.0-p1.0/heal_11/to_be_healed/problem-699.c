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

enum {
    INITIAL_STRING_CAPACITY = 64
};

static enum ReadStatus grow_buffer(char **buffer, size_t *capacity)
{
    if (buffer == NULL || *buffer == NULL ||
        capacity == NULL || *capacity == 0) {
        return READ_ERROR;
    }

    if (*capacity > SIZE_MAX / 2) {
        return READ_NO_MEMORY;
    }

    size_t new_capacity = *capacity * 2;
    char *new_buffer = realloc(*buffer, new_capacity);

    if (new_buffer == NULL) {
        return READ_NO_MEMORY;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;

    return READ_OK;
}

static enum ReadStatus read_string(FILE *stream,
                                   char **result,
                                   size_t *result_length)
{
    char *buffer;
    size_t capacity = INITIAL_STRING_CAPACITY;
    size_t length = 0;

    if (stream == NULL || result == NULL || result_length == NULL) {
        return READ_ERROR;
    }

    *result = NULL;
    *result_length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return READ_NO_MEMORY;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return READ_ERROR;
            }

            if (length == 0) {
                free(buffer);
                return READ_END;
            }

            break;
        }

        if (isspace((unsigned char)ch)) {
            if (length == 0) {
                continue;
            }

            break;
        }

        if (length >= capacity - 1) {
            enum ReadStatus status = grow_buffer(&buffer, &capacity);

            if (status != READ_OK) {
                free(buffer);
                return status;
            }
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *result = buffer;
    *result_length = length;

    return READ_OK;
}

static bool minimum_swaps(const char *source,
                          size_t source_length,
                          const char *target,
                          size_t target_length,
                          size_t *swaps)
{
    size_t zero_to_one = 0;
    size_t one_to_zero = 0;

    if (source == NULL || target == NULL || swaps == NULL) {
        return false;
    }

    if (source_length != target_length) {
        return false;
    }

    for (size_t i = 0; i < source_length; ++i) {
        if ((source[i] != '0' && source[i] != '1') ||
            (target[i] != '0' && target[i] != '1')) {
            return false;
        }

        if (source[i] == '0' && target[i] == '1') {
            ++zero_to_one;
        } else if (source[i] == '1' && target[i] == '0') {
            ++one_to_zero;
        }
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
    size_t source_length = 0;
    size_t target_length = 0;
    size_t swaps = 0;
    int exit_status = EXIT_FAILURE;

    enum ReadStatus status =
        read_string(stdin, &source, &source_length);

    if (status != READ_OK) {
        fputs("Failed to read the source string.\n", stderr);
        goto cleanup;
    }

    status = read_string(stdin, &target, &target_length);

    if (status != READ_OK) {
        fputs("Failed to read the target string.\n", stderr);
        goto cleanup;
    }

    if (!minimum_swaps(source, source_length,
                       target, target_length, &swaps)) {
        if (puts("-1") == EOF) {
            goto cleanup;
        }
    } else if (printf("%zu\n", swaps) < 0) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(source);
    free(target);

    return exit_status;
}