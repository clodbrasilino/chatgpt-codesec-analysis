#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int read_token(char **token)
{
    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    size_t length = 0;
    size_t capacity = 32;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF) {
        free(buffer);
        return 0;
    }

    for (;;) {
        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character == EOF || isspace((unsigned char)character)) {
            break;
        }
    }

    if (character == EOF && ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_int64(int64_t *value)
{
    if (value == NULL) {
        return 0;
    }

    char *token = NULL;

    if (!read_token(&token)) {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(token, &end, 10);

    int valid = end != token &&
                *end == '\0' &&
                errno != ERANGE &&
                parsed >= INT64_MIN &&
                parsed <= INT64_MAX;

    if (valid) {
        *value = (int64_t)parsed;
    }

    free(token);
    return valid;
}

static int read_size(size_t *value)
{
    if (value == NULL) {
        return 0;
    }

    char *token = NULL;

    if (!read_token(&token)) {
        return 0;
    }

    if (token[0] == '-') {
        free(token);
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(token, &end, 10);

    int valid = end != token &&
                *end == '\0' &&
                errno != ERANGE &&
                parsed <= SIZE_MAX;

    if (valid) {
        *value = (size_t)parsed;
    }

    free(token);
    return valid;
}

static int read_header(size_t *length, int64_t *difference)
{
    if (length == NULL || difference == NULL) {
        return 0;
    }

    return read_size(length) && read_int64(difference);
}

static int has_difference(int64_t next, int64_t current, int64_t difference)
{
    if (difference > 0) {
        return current <= INT64_MAX - difference &&
               next == current + difference;
    }

    if (difference < 0) {
        return current >= INT64_MIN - difference &&
               next == current + difference;
    }

    return next == current;
}

static size_t max_subsequence_length(const int64_t *array,
                                     size_t length,
                                     int64_t difference)
{
    if (array == NULL || length == 0) {
        return 0;
    }

    size_t best = 1;

    for (size_t i = 0; i < length; ++i) {
        size_t current_length = 1;
        int64_t current_value = array[i];

        for (size_t j = i + 1; j < length; ++j) {
            if (has_difference(array[j], current_value, difference)) {
                current_value = array[j];

                if (current_length < SIZE_MAX) {
                    ++current_length;
                }
            }
        }

        if (current_length > best) {
            best = current_length;
        }
    }

    return best;
}

int main(void)
{
    size_t length = 0;
    int64_t difference = 0;

    if (!read_header(&length, &difference)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int64_t)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        puts("0");
        return EXIT_SUCCESS;
    }

    int64_t *array = malloc(length * sizeof(*array));

    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", max_subsequence_length(array, length, difference));

    free(array);
    return EXIT_SUCCESS;
}