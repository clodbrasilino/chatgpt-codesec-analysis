#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int count_substrings(const unsigned char *data, size_t length,
                            size_t *result)
{
    size_t frequencies[256] = {0};
    size_t total = 0;

    if ((data == NULL && length != 0U) || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = frequencies[data[i]];

        if (frequency == SIZE_MAX ||
            frequency > SIZE_MAX - 1U ||
            total > SIZE_MAX - (frequency + 1U)) {
            return -1;
        }

        ++frequency;
        total += frequency;
        frequencies[data[i]] = frequency;
    }

    *result = total;
    return 0;
}

static int append_bytes(unsigned char **data, size_t *length, size_t *capacity,
                        const unsigned char *source, size_t count)
{
    if (data == NULL || length == NULL || capacity == NULL ||
        (source == NULL && count != 0U) ||
        *length > *capacity ||
        (*data == NULL && *capacity != 0U)) {
        return -1;
    }

    if (count > SIZE_MAX - *length) {
        return -1;
    }

    size_t required = *length + count;

    if (required > *capacity) {
        size_t new_capacity = *capacity;

        if (new_capacity == 0U) {
            new_capacity = required > 4096U ? required : 4096U;
        }

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2U) {
                new_capacity = required;
                break;
            }
            new_capacity *= 2U;
        }

        unsigned char *new_data = realloc(*data, new_capacity);
        if (new_data == NULL) {
            return -1;
        }

        *data = new_data;
        *capacity = new_capacity;
    }

    if (count != 0U) {
        memmove(*data + *length, source, count);
    }

    *length = required;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t count = 0;
    int status = EXIT_FAILURE;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

        if (bytes_read > 0U) {
            const unsigned char *newline = memchr(buffer, '\n', bytes_read);
            size_t line_bytes = newline == NULL
                                    ? bytes_read
                                    : (size_t)(newline - buffer);

            if (append_bytes(&input, &length, &capacity,
                             buffer, line_bytes) != 0) {
                goto cleanup;
            }

            if (newline != NULL) {
                break;
            }
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }
    }

    if (count_substrings(input, length, &count) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", count) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}