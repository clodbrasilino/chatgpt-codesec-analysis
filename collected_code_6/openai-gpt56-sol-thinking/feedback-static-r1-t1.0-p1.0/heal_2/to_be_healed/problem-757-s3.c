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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t position;
    size_t length;
} Reader;

static int reader_get_byte(Reader *reader, unsigned char *byte)
{
    if (reader == NULL || reader->stream == NULL || byte == NULL) {
        return -1;
    }

    if (reader->position == reader->length) {
        reader->length = fread(reader->buffer, 1, sizeof(reader->buffer),
                               reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            return ferror(reader->stream) ? -1 : 0;
        }
    }

    *byte = reader->buffer[reader->position++];
    return 1;
}

static int read_token(Reader *reader, String *token)
{
    char *buffer;
    char *resized;
    size_t capacity = 32;
    size_t length = 0;
    unsigned char byte;
    int status;

    if (reader == NULL || token == NULL) {
        return -1;
    }

    token->data = NULL;
    token->length = 0;

    for (;;) {
        status = reader_get_byte(reader, &byte);
        if (status != 1) {
            return status;
        }

        if (!isspace(byte)) {
            break;
        }
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        if (byte == '\0') {
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

        buffer[length++] = (char)byte;

        status = reader_get_byte(reader, &byte);
        if (status < 0) {
            free(buffer);
            return -1;
        }

        if (status == 0 || isspace(byte)) {
            break;
        }
    }

    buffer[length] = '\0';
    token->data = buffer;
    token->length = length;
    return 1;
}

static int parse_size(const String *text, size_t *value)
{
    size_t result = 0;
    size_t i;

    if (text == NULL || value == NULL || text->data == NULL ||
        text->length == 0) {
        return -1;
    }

    for (i = 0; i < text->length; ++i) {
        size_t digit;

        if (text->data[i] < '0' || text->data[i] > '9') {
            return -1;
        }

        digit = (size_t)(text->data[i] - '0');
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
        first->data == NULL || second->data == NULL ||
        first->length != second->length) {
        return 0;
    }

    for (i = 0; i < first->length; ++i) {
        if (first->data[i] != second->data[first->length - i - 1]) {
            return 0;
        }
    }

    return 1;
}

int count_reverse_pairs(const String strings[], size_t count,
                        uintmax_t *result)
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

static void free_strings(String strings[], size_t count)
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
    Reader reader = {0};
    String count_token = {NULL, 0};
    String *strings = NULL;
    size_t count;
    size_t i;
    uintmax_t pairs;
    int status;

    reader.stream = stdin;

    status = read_token(&reader, &count_token);
    if (status != 1 || parse_size(&count_token, &count) != 0) {
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
        status = read_token(&reader, &strings[i]);
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