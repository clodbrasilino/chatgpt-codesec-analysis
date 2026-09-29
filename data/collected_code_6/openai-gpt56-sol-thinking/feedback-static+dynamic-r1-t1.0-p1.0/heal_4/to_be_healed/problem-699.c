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
    unsigned char buffer[4096];
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
        reader->length = fread(reader->buffer,
                               sizeof(reader->buffer[0]),
                               sizeof(reader->buffer),
                               reader->stream);
        reader->position = 0;

        if (reader->length == 0) {
            if (ferror(reader->stream)) {
                return READ_ERROR;
            }

            if (feof(reader->stream)) {
                return READ_END;
            }

            return READ_ERROR;
        }
    }

    *value = reader->buffer[reader->position];
    ++reader->position;
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
        new_capacity = SIZE_MAX;
    } else {
        new_capacity = *capacity * 2;
    }

    if (new_capacity <= *capacity) {
        return READ_NO_MEMORY;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return READ_NO_MEMORY;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return READ_OK;
}

static enum ReadStatus read_string(struct InputReader *reader, char **result)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;

    if (reader == NULL || result == NULL) {
        return READ_ERROR;
    }

    *result = NULL;

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

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return READ_NO_MEMORY;
        }

        if (length + 1 >= capacity) {
            status = grow_buffer(&buffer, &capacity);
            if (status != READ_OK) {
                free(buffer);
                return status;
            }
        }

        buffer[length] = (char)ch;
        ++length;
    }

    buffer[length] = '\0';
    *result = buffer;
    return READ_OK;
}

static bool minimum_swaps(const char *source,
                          const char *target,
                          size_t *swaps)
{
    size_t zero_to_one = 0;
    size_t one_to_zero = 0;
    size_t i = 0;

    if (source == NULL || target == NULL || swaps == NULL) {
        return false;
    }

    while (source[i] != '\0' && target[i] != '\0') {
        if ((source[i] != '0' && source[i] != '1') ||
            (target[i] != '0' && target[i] != '1')) {
            return false;
        }

        if (source[i] == '0' && target[i] == '1') {
            ++zero_to_one;
        } else if (source[i] == '1' && target[i] == '0') {
            ++one_to_zero;
        }

        ++i;
    }

    if (source[i] != '\0' ||
        target[i] != '\0' ||
        zero_to_one != one_to_zero) {
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
    size_t swaps = 0;
    enum ReadStatus status;

    status = read_string(&reader, &source);
    if (status != READ_OK) {
        fputs("Failed to read the source string.\n", stderr);
        return EXIT_FAILURE;
    }

    status = read_string(&reader, &target);
    if (status != READ_OK) {
        free(source);
        fputs("Failed to read the target string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!minimum_swaps(source, target, &swaps)) {
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