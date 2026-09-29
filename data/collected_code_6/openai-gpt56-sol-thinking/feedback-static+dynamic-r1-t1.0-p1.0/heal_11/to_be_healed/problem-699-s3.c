#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TOKEN_LENGTH ((size_t)1048576)
#define READER_BUFFER_SIZE ((size_t)4096)

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[READER_BUFFER_SIZE];
    size_t position;
    size_t available;
    int end_of_file;
    int io_error;
} InputReader;

static int reader_get(InputReader *reader)
{
    size_t bytes_read;

    if (reader == NULL || reader->stream == NULL) {
        return EOF;
    }

    if (reader->position < reader->available) {
        return (int)reader->buffer[reader->position++];
    }

    if (reader->io_error || reader->end_of_file) {
        return EOF;
    }

    bytes_read = fread(reader->buffer, 1, sizeof(reader->buffer),
                       reader->stream);

    reader->position = 0;
    reader->available = bytes_read;

    if (ferror(reader->stream)) {
        reader->io_error = 1;
    }

    if (feof(reader->stream)) {
        reader->end_of_file = 1;
    }

    if (bytes_read == 0) {
        return EOF;
    }

    return (int)reader->buffer[reader->position++];
}

static int read_token(InputReader *reader, char **output,
                      size_t *output_length)
{
    const size_t maximum_capacity = MAX_TOKEN_LENGTH + 1;
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    int ch;

    if (output == NULL || output_length == NULL) {
        return -1;
    }

    *output = NULL;
    *output_length = 0;

    if (reader == NULL || reader->stream == NULL) {
        return -1;
    }

    do {
        ch = reader_get(reader);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return reader->io_error ? -1 : 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;
        char *new_buffer;

        if (ch == '\0' || length >= MAX_TOKEN_LENGTH) {
            free(buffer);
            return -1;
        }

        if (length >= capacity - 1) {
            if (capacity >= maximum_capacity) {
                free(buffer);
                return -1;
            }

            if (capacity > maximum_capacity / 2) {
                new_capacity = maximum_capacity;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity ||
                new_capacity > maximum_capacity) {
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

    if (reader->io_error) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *output = buffer;
    *output_length = length;

    return 1;
}

static int validate_binary_string(const char *string, size_t length)
{
    size_t i;

    if (string == NULL || length > MAX_TOKEN_LENGTH) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        if (string[i] != '0' && string[i] != '1') {
            return -1;
        }
    }

    return 0;
}

static int minimum_swaps(const char *source, size_t source_length,
                         const char *target, size_t target_length,
                         size_t *result)
{
    size_t zero_to_one = 0;
    size_t one_to_zero = 0;
    size_t i;

    if (source == NULL || target == NULL || result == NULL) {
        return -1;
    }

    *result = 0;

    if (validate_binary_string(source, source_length) != 0 ||
        validate_binary_string(target, target_length) != 0) {
        return -1;
    }

    if (source_length != target_length) {
        return 1;
    }

    for (i = 0; i < source_length; ++i) {
        if (source[i] == target[i]) {
            continue;
        }

        if (source[i] == '0') {
            ++zero_to_one;
        } else {
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
    InputReader reader = {
        stdin,
        { 0 },
        0,
        0,
        0,
        0
    };
    char *source = NULL;
    char *target = NULL;
    size_t source_length = 0;
    size_t target_length = 0;
    size_t swaps = 0;
    int status;
    int exit_status = EXIT_FAILURE;

    if (read_token(&reader, &source, &source_length) != 1) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (read_token(&reader, &target, &target_length) != 1) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    status = minimum_swaps(source, source_length,
                           target, target_length, &swaps);

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