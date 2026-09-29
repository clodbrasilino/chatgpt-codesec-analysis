#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int are_reverses(const char *first, const char *second)
{
    size_t first_length;
    size_t second_length;
    size_t i;

    if (first == NULL || second == NULL) {
        return 0;
    }

    first_length = strlen(first);
    second_length = strlen(second);

    if (first_length != second_length) {
        return 0;
    }

    for (i = 0; i < first_length; ++i) {
        if (first[i] != second[first_length - i - 1]) {
            return 0;
        }
    }

    return 1;
}

int count_reverse_pairs(const char *const strings[], size_t count,
                        uintmax_t *result)
{
    uintmax_t pairs = 0;
    size_t i;
    size_t j;

    if (result == NULL || (count != 0 && strings == NULL)) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }

        for (j = i + 1; j < count; ++j) {
            if (strings[j] == NULL) {
                return -1;
            }

            if (are_reverses(strings[i], strings[j])) {
                if (pairs == UINTMAX_MAX) {
                    return -1;
                }

                ++pairs;
            }
        }
    }

    *result = pairs;
    return 0;
}

static int read_token(FILE *stream, const char **token)
{
    char *buffer;
    char *resized;
    size_t capacity = 32;
    size_t length = 0;
    int ch;

    if (stream == NULL || token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        ch = fgetc(stream);
        if (ch == EOF) {
            return ferror(stream) ? -1 : 0;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (ch == '\0') {
            free(buffer);
            return -1;
        }

        if (length == capacity - 1) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = fgetc(stream);
    }

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *token = buffer;

    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    size_t result = 0;
    size_t i;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return -1;
    }

    for (i = 0; text[i] != '\0'; ++i) {
        size_t digit;

        if (text[i] < '0' || text[i] > '9') {
            return -1;
        }

        digit = (size_t)(text[i] - '0');
        if (result > (SIZE_MAX - digit) / 10) {
            return -1;
        }

        result = result * 10 + digit;
    }

    *value = result;
    return 0;
}

static void free_strings(const char *const strings[], size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free((void *)strings[i]);
    }

    free((void *)strings);
}

int main(void)
{
    const char *count_token = NULL;
    const char **strings = NULL;
    size_t count;
    size_t i;
    uintmax_t pairs;
    int status;

    status = read_token(stdin, &count_token);
    if (status != 1 || parse_size(count_token, &count) != 0) {
        free((void *)count_token);
        fputs("Invalid string count\n", stderr);
        return EXIT_FAILURE;
    }

    free((void *)count_token);

    if (count > SIZE_MAX / sizeof(*strings)) {
        fputs("String count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        strings = calloc(count, sizeof(*strings));
        if (strings == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < count; ++i) {
        status = read_token(stdin, &strings[i]);
        if (status != 1) {
            free_strings(strings, count);
            fputs("Failed to read string list\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (count_reverse_pairs(strings, count, &pairs) != 0) {
        free_strings(strings, count);
        fputs("Failed to count reverse pairs\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", pairs);
    free_strings(strings, count);

    return EXIT_SUCCESS;
}