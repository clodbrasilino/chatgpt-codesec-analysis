#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t position;
    size_t length;
} InputReader;

static int binary_string_length(const char *string, size_t *length)
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

    if (binary_string_length(source, &source_length) != 0 ||
        binary_string_length(target, &target_length) != 0) {
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

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || *buffer == NULL ||
        capacity == NULL || *capacity == 0) {
        return -1;
    }

    if (*capacity > SIZE_MAX / 2) {
        return -1;
    }

    new_capacity = *capacity * 2;
    new_buffer = realloc(*buffer, new_capacity);

    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int input_reader_get(InputReader *reader, unsigned char *character)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'bytes_read' can be reduced. [variableScope]
     */
    size_t bytes_read;

    if (reader == NULL || reader->stream == NULL || character == NULL) {
        return -1;
    }

    if (reader->position == reader->length) {
        bytes_read = fread(reader->buffer, 1, sizeof(reader->buffer),
                           reader->stream);

        reader->position = 0;
        reader->length = bytes_read;

        if (bytes_read == 0) {
            return ferror(reader->stream) ? -1 : 0;
        }
    }

    *character = reader->buffer[reader->position++];
    return 1;
}

static int read_token(InputReader *reader, char **output)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    unsigned char character;
    int status;

    if (reader == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    do {
        status = input_reader_get(reader, &character);
        if (status <= 0) {
            return status;
        }
    } while (isspace(character));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        if (character == '\0') {
            free(buffer);
            return -1;
        }

        if (isspace(character)) {
            break;
        }

        if (length == capacity - 1) {
            if (grow_buffer(&buffer, &capacity) != 0) {
                free(buffer);
                return -1;
            }
        }

        buffer[length++] = (char)character;

        status = input_reader_get(reader, &character);
        if (status < 0) {
            free(buffer);
            return -1;
        }

        if (status == 0) {
            break;
        }
    }

    buffer[length] = '\0';
    *output = buffer;
    return 1;
}

int main(void)
{
    InputReader reader = { stdin, { 0 }, 0, 0 };
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