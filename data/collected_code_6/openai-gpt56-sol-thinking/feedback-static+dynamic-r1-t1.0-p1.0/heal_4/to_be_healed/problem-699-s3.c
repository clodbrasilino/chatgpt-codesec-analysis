#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 4096U
#define MAX_TOKEN_LENGTH 1048576U

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t available;
    int error;
} InputReader;

static int reader_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL) {
        return EOF;
    }

    if (reader->position == reader->available) {
        reader->available = fread(
            reader->buffer,
            sizeof(reader->buffer[0]),
            INPUT_BUFFER_SIZE,
            reader->stream
        );
        reader->position = 0;

        if (reader->available == 0) {
            if (ferror(reader->stream)) {
                reader->error = 1;
            }
            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static int read_token(InputReader *reader, char **output)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    int ch;

    if (reader == NULL || reader->stream == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    do {
        ch = reader_get(reader);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        free(buffer);
        return reader->error ? -1 : 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        char *new_buffer;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (ch == '\0' || length >= MAX_TOKEN_LENGTH) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            if (capacity > ((size_t)MAX_TOKEN_LENGTH + 1) / 2) {
                new_capacity = (size_t)MAX_TOKEN_LENGTH + 1;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return -1;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
        ch = reader_get(reader);
    }

    if (ch == EOF && reader->error) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *output = buffer;
    return 1;
}

static int validate_binary_string(const char *string, size_t *length)
{
    size_t i;

    if (string == NULL || length == NULL) {
        return -1;
    }

    for (i = 0; string[i] != '\0'; ++i) {
        if (string[i] != '0' && string[i] != '1') {
            return -1;
        }
    }

    *length = i;
    return 0;
}

int minimum_swaps(const char *source, const char *target, size_t *result)
{
    size_t source_length;
    size_t target_length;
    size_t zero_to_one = 0;
    size_t one_to_zero = 0;
    size_t i;

    if (source == NULL || target == NULL || result == NULL) {
        return -1;
    }

    if (validate_binary_string(source, &source_length) != 0 ||
        validate_binary_string(target, &target_length) != 0) {
        return -1;
    }

    if (source_length != target_length) {
        return 1;
    }

    for (i = 0; i < source_length; ++i) {
        if (source[i] == '0' && target[i] == '1') {
            ++zero_to_one;
        } else if (source[i] == '1' && target[i] == '0') {
            ++one_to_zero;
        }
    }

    if (zero_to_one != one_to_zero) {
        return 1;
    }

    *result = zero_to_one;
    return 0;
}

int main(void)
{
    InputReader reader = { stdin, { 0 }, 0, 0, 0 };
    char *source = NULL;
    char *target = NULL;
    size_t swaps = 0;
    int read_status;
    int status;
    int exit_status = EXIT_FAILURE;

    read_status = read_token(&reader, &source);
    if (read_status != 1) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    read_status = read_token(&reader, &target);
    if (read_status != 1) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    status = minimum_swaps(source, target, &swaps);
    if (status < 0) {
        fputs("Invalid binary string\n", stderr);
        goto cleanup;
    }

    if (status > 0) {
        puts("-1");
    } else {
        printf("%zu\n", swaps);
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(target);
    free(source);
    return exit_status;
}