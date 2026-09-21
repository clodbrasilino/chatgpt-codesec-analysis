#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *data;
    size_t length;
} String;

typedef struct {
    FILE *stream;
} Reader;

static int reader_get(Reader *reader, unsigned char *ch)
{
    int value;

    if (reader == NULL || reader->stream == NULL || ch == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    value = fgetc(reader->stream);

    if (value == EOF) {
        return ferror(reader->stream) ? -1 : 0;
    }

    *ch = (unsigned char)value;
    return 1;
}

static int read_token(Reader *reader, char **token, size_t *token_length)
{
    char *buffer;
    size_t capacity = 32;
    size_t length = 0;
    unsigned char ch;
    int status;

    if (reader == NULL || token == NULL || token_length == NULL) {
        return -1;
    }

    *token = NULL;
    *token_length = 0;

    do {
        status = reader_get(reader, &ch);
        if (status <= 0) {
            return status;
        }
    } while (isspace((int)ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (ch == '\0') {
            free(buffer);
            return -1;
        }

        if (length == capacity - 1) {
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

        status = reader_get(reader, &ch);

        if (status < 0) {
            free(buffer);
            return -1;
        }

        if (status == 0 || isspace((int)ch)) {
            break;
        }
    }

    buffer[length] = '\0';
    *token = buffer;
    *token_length = length;

    return 1;
}

static int parse_size(const char *text, size_t length, size_t *value)
{
    size_t result = 0;
    size_t i;

    if (text == NULL || value == NULL || length == 0) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
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

static int are_reverses(const String *first, const String *second)
{
    size_t i;

    if (first == NULL || second == NULL ||
        first->data == NULL || second->data == NULL) {
        return 0;
    }

    if (first->length != second->length) {
        return 0;
    }

    for (i = 0; i < first->length; ++i) {
        if (first->data[i] != second->data[first->length - i - 1]) {
            return 0;
        }
    }

    return 1;
}

int count_reverse_pairs(
    const String strings[],
    size_t count,
    uintmax_t *result
)
{
    uintmax_t pairs = 0;
    size_t i;
    size_t j;

    if (result == NULL || (count != 0 && strings == NULL)) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i].data == NULL) {
            return -1;
        }
    }

    for (i = 0; i < count; ++i) {
        for (j = i + 1; j < count; ++j) {
            if (are_reverses(&strings[i], &strings[j])) {
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

static void free_strings(String *strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(strings[i].data);
    }

    free(strings);
}

int main(void)
{
    Reader reader = { stdin };
    String count_token = { NULL, 0 };
    String *strings = NULL;
    size_t count;
    size_t i;
    uintmax_t pairs;
    int status;

    status = read_token(
        &reader,
        &count_token.data,
        &count_token.length
    );

    if (status != 1 ||
        parse_size(count_token.data, count_token.length, &count) != 0) {
        free(count_token.data);
        fputs("Invalid string count\n", stderr);
        return EXIT_FAILURE;
    }

    free(count_token.data);

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
        status = read_token(
            &reader,
            &strings[i].data,
            &strings[i].length
        );

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

    if (printf("%" PRIuMAX "\n", pairs) < 0) {
        free_strings(strings, count);
        fputs("Failed to write result\n", stderr);
        return EXIT_FAILURE;
    }

    free_strings(strings, count);
    return EXIT_SUCCESS;
}