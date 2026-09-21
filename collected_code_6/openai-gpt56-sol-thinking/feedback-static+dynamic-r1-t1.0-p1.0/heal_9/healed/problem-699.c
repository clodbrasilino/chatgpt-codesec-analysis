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
    INPUT_BUFFER_SIZE = 4096,
    INITIAL_STRING_CAPACITY = 64
};

struct InputReader {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
};

static enum ReadStatus read_byte(struct InputReader *reader,
                                 unsigned char *value)
{
    if (reader == NULL || reader->stream == NULL || value == NULL) {
        return READ_ERROR;
    }

    if (reader->position == reader->length) {
        reader->length = fread(reader->buffer, 1,
                               sizeof reader->buffer, reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            return ferror(reader->stream) ? READ_ERROR : READ_END;
        }
    }

    *value = reader->buffer[reader->position++];
    return READ_OK;
}

static enum ReadStatus grow_buffer(char **buffer, size_t *capacity)
{
    char *new_buffer;
    size_t new_capacity;

    if (buffer == NULL || *buffer == NULL ||
        capacity == NULL || *capacity == 0) {
        return READ_ERROR;
    }

    if (*capacity > SIZE_MAX / 2) {
        return READ_NO_MEMORY;
    }

    new_capacity = *capacity * 2;
    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return READ_NO_MEMORY;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return READ_OK;
}

static enum ReadStatus read_string(struct InputReader *reader,
                                   char **result,
                                   size_t *result_length)
{
    char *buffer;
    size_t capacity = INITIAL_STRING_CAPACITY;
    size_t length = 0;

    if (reader == NULL || result == NULL || result_length == NULL) {
        return READ_ERROR;
    }

    *result = NULL;
    *result_length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return READ_NO_MEMORY;
    }

    for (;;) {
        unsigned char ch;
        enum ReadStatus status = read_byte(reader, &ch);

        if (status == READ_END) {
            if (length == 0) {
                free(buffer);
                return READ_END;
            }
            break;
        }

        if (status != READ_OK) {
            free(buffer);
            return status;
        }

        if (isspace((int)ch)) {
            if (length == 0) {
                continue;
            }
            break;
        }

        if (length == capacity - 1) {
            status = grow_buffer(&buffer, &capacity);
            if (status != READ_OK) {
                free(buffer);
                return status;
            }
        }

        buffer[length++] = (char)ch;
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
    struct InputReader reader = {
        .stream = stdin,
        .position = 0,
        .length = 0
    };
    char *source = NULL;
    char *target = NULL;
    size_t source_length = 0;
    size_t target_length = 0;
    size_t swaps = 0;
    enum ReadStatus status;
    int exit_status = EXIT_FAILURE;

    status = read_string(&reader, &source, &source_length);
    if (status != READ_OK) {
        fputs("Failed to read the source string.\n", stderr);
        goto cleanup;
    }

    status = read_string(&reader, &target, &target_length);
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