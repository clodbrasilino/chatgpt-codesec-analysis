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

struct InputReader {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char data[4096];
    size_t position;
    size_t available;
};

static enum ReadStatus read_byte(struct InputReader *reader,
                                 unsigned char *value)
{
    if (reader == NULL || reader->stream == NULL || value == NULL) {
        return READ_ERROR;
    }

    if (reader->position == reader->available) {
        reader->available = fread(reader->data, 1, sizeof(reader->data),
                                  reader->stream);
        reader->position = 0;

        if (reader->available == 0) {
            if (ferror(reader->stream)) {
                return READ_ERROR;
            }

            if (feof(reader->stream)) {
                return READ_END;
            }

            return READ_ERROR;
        }
    }

    *value = reader->data[reader->position++];
    return READ_OK;
}

static enum ReadStatus grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *new_buffer;

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
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;

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

        if (isspace(ch)) {
            if (length == 0) {
                continue;
            }
            break;
        }

        if (length >= capacity - 1) {
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
    size_t i;

    if (source == NULL || target == NULL || swaps == NULL) {
        return false;
    }

    if (source_length != target_length) {
        return false;
    }

    for (i = 0; i < source_length; ++i) {
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
    struct InputReader reader = { stdin, { 0 }, 0, 0 };
    char *source = NULL;
    char *target = NULL;
    size_t source_length = 0;
    size_t target_length = 0;
    size_t swaps = 0;
    enum ReadStatus status;

    status = read_string(&reader, &source, &source_length);
    if (status != READ_OK) {
        fputs("Failed to read the source string.\n", stderr);
        return EXIT_FAILURE;
    }

    status = read_string(&reader, &target, &target_length);
    if (status != READ_OK) {
        free(source);
        fputs("Failed to read the target string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!minimum_swaps(source, source_length,
                       target, target_length, &swaps)) {
        free(source);
        free(target);

        if (puts("-1") == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    free(source);
    free(target);

    if (printf("%zu\n", swaps) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}