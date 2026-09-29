#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TOKEN_LENGTH ((size_t)1048576)

typedef struct {
    FILE *stream;
    int error;
} InputReader;

static int reader_get(InputReader *reader)
{
    int ch;

    if (reader == NULL || reader->stream == NULL) {
        return EOF;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = fgetc(reader->stream);
    if (ch == EOF && ferror(reader->stream)) {
        reader->error = 1;
    }

    return ch;
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
        if (ch == '\0' || length == MAX_TOKEN_LENGTH) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > (MAX_TOKEN_LENGTH + 1) / 2) {
                new_capacity = MAX_TOKEN_LENGTH + 1;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity ||
                new_capacity > MAX_TOKEN_LENGTH + 1) {
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
    size_t i = 0;

    if (string == NULL || length == NULL) {
        return -1;
    }

    while (i < MAX_TOKEN_LENGTH && string[i] != '\0') {
        if (string[i] != '0' && string[i] != '1') {
            return -1;
        }

        ++i;
    }

    if (string[i] != '\0') {
        return -1;
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
    InputReader reader = {
        .stream = stdin,
        .error = 0
    };
    char *source = NULL;
    char *target = NULL;
    size_t swaps = 0;
    int status;
    int exit_status = EXIT_FAILURE;

    if (read_token(&reader, &source) != 1) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (read_token(&reader, &target) != 1) {
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