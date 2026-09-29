#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int longest_repeating_subsequence(const unsigned char *str,
                                         size_t length,
                                         size_t *result)
{
    size_t columns;
    size_t *previous;
    size_t *current;

    if (result == NULL || (str == NULL && length != 0) ||
        length == SIZE_MAX) {
        return -1;
    }

    columns = length + 1;

    if (columns > SIZE_MAX / sizeof(*previous)) {
        return -1;
    }

    previous = calloc(columns, sizeof(*previous));
    current = calloc(columns, sizeof(*current));

    if (previous == NULL || current == NULL) {
        free(previous);
        free(current);
        return -1;
    }

    for (size_t i = 1; i <= length; ++i) {
        current[0] = 0;

        for (size_t j = 1; j <= length; ++j) {
            if (i != j && str[i - 1] == str[j - 1]) {
                current[j] = previous[j - 1] + 1;
            } else {
                current[j] = previous[j] > current[j - 1]
                                 ? previous[j]
                                 : current[j - 1];
            }
        }

        size_t *temporary = previous;
        previous = current;
        current = temporary;
    }

    *result = previous[length];

    free(previous);
    free(current);
    return 0;
}

static int read_line(FILE *stream, unsigned char **buffer, size_t *length)
{
    unsigned char *data;
    size_t used = 0;
    size_t capacity = 64;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        unsigned char block[4096];
        size_t count = fread(block, 1, sizeof(block), stream);
        size_t line_count = count;

        for (size_t i = 0; i < count; ++i) {
            if (block[i] == '\n') {
                line_count = i;

                if (i + 1 < count) {
                    size_t unread = count - i - 1;

                    if (fseek(stream, -(long)unread, SEEK_CUR) != 0) {
                        for (size_t k = count; k > i + 1; --k) {
                            if (ungetc(block[k - 1], stream) == EOF) {
                                free(data);
                                return -1;
                            }
                        }
                    }
                }
                break;
            }
        }

        if (line_count > SIZE_MAX - used) {
            free(data);
            return -1;
        }

        size_t required = used + line_count;

        if (required > capacity) {
            size_t new_capacity = capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            unsigned char *new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return -1;
            }

            data = new_data;
            capacity = new_capacity;
        }

        for (size_t i = 0; i < line_count; ++i) {
            data[used + i] = block[i];
        }
        used = required;

        if (line_count < count || count < sizeof(block)) {
            if (ferror(stream)) {
                free(data);
                return -1;
            }
            break;
        }
    }

    if (used > 0 && data[used - 1] == '\r') {
        --used;
    }

    *buffer = data;
    *length = used;
    return 0;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t length = 0;
    size_t result;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &input, &length) != 0) {
        goto cleanup;
    }

    if (longest_repeating_subsequence(input, length, &result) != 0) {
        goto cleanup;
    }

    if (printf("%zu\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}