#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_swaps(const char *str, size_t length, size_t *result)
{
    size_t balance = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (str == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        switch (str[i]) {
        case '[':
            if (imbalance > 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return 0;
                }
                swaps += imbalance;
                --imbalance;
            } else {
                if (balance == SIZE_MAX) {
                    return 0;
                }
                ++balance;
            }
            break;

        case ']':
            if (balance > 0) {
                --balance;
            } else {
                if (imbalance == SIZE_MAX) {
                    return 0;
                }
                ++imbalance;
            }
            break;

        default:
            return 0;
        }
    }

    if (balance != 0 || imbalance != 0) {
        return 0;
    }

    *result = swaps;
    return 1;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL) {
        return 0;
    }

    if (required <= *capacity) {
        return 1;
    }

    new_capacity = *capacity == 0 ? 64 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data = NULL;
    size_t capacity = 0;
    size_t used = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char chunk[4096];

    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;

    for (;;) {
        size_t count = fread(chunk, 1, sizeof(chunk), stream);

        for (size_t i = 0; i < count; ++i) {
            if (chunk[i] == '\n') {
                size_t unread = count - i - 1;

                if (unread > 0) {
                    if (fseek(stream, -(long)unread, SEEK_CUR) != 0) {
                        for (size_t j = count; j > i + 1; --j) {
                            if (ungetc(chunk[j - 1], stream) == EOF) {
                                free(data);
                                return 0;
                            }
                        }
                    }
                }

                if (used > 0 && data[used - 1] == '\r') {
                    --used;
                }

                *buffer = data;
                *length = used;
                return 1;
            }

            if (used == SIZE_MAX) {
                free(data);
                return 0;
            }

            if (!grow_buffer(&data, &capacity, used + 1)) {
                free(data);
                return 0;
            }

            data[used++] = (char)chunk[i];
        }

        if (count < sizeof(chunk)) {
            if (ferror(stream)) {
                free(data);
                return 0;
            }
            break;
        }
    }

    if (used > 0 && data[used - 1] == '\r') {
        --used;
    }

    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t swaps = 0;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &input, &length)) {
        fputs("Failed to read input\n", stderr);
        goto cleanup;
    }

    if (!minimum_swaps(input != NULL ? input : "", length, &swaps)) {
        fputs("Invalid bracket string\n", stderr);
        goto cleanup;
    }

    if (printf("%zu\n", swaps) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}