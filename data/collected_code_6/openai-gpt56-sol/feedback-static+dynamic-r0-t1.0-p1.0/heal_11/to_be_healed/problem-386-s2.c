#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_swaps(const char *str, size_t length, size_t *result)
{
    size_t balance = 0;
    size_t unmatched_closes = 0;
    size_t open_count = 0;
    size_t close_count = 0;
    size_t swaps = 0;

    if (str == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == '[') {
            if (open_count == SIZE_MAX) {
                return 0;
            }
            ++open_count;

            if (unmatched_closes > 0) {
                if (swaps > SIZE_MAX - unmatched_closes) {
                    return 0;
                }
                swaps += unmatched_closes;
                --unmatched_closes;
            } else {
                if (balance == SIZE_MAX) {
                    return 0;
                }
                ++balance;
            }
        } else if (str[i] == ']') {
            if (close_count == SIZE_MAX) {
                return 0;
            }
            ++close_count;

            if (balance > 0) {
                --balance;
            } else {
                if (unmatched_closes == SIZE_MAX) {
                    return 0;
                }
                ++unmatched_closes;
            }
        } else {
            return 0;
        }
    }

    if (open_count != close_count) {
        return 0;
    }

    *result = swaps;
    return 1;
}

static int read_bracket_string(FILE *stream, char **buffer, size_t *length)
{
    char *data;
    size_t used = 0;
    size_t capacity = 64;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;

    data = malloc(capacity);
    if (data == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(data);
                return 0;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(data);
                    return 0;
                }
                break;
            }

            if (next != '\n') {
                free(data);
                return -1;
            }
            break;
        }

        if (character != '[' && character != ']') {
            free(data);
            return -1;
        }

        if (used == capacity) {
            size_t new_capacity;
            char *new_data;

            if (capacity > SIZE_MAX / 2) {
                free(data);
                return 0;
            }

            new_capacity = capacity * 2;
            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return 0;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[used++] = (char)character;
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
    int read_status;
    int status = EXIT_FAILURE;

    read_status = read_bracket_string(stdin, &input, &length);

    if (read_status < 0) {
        fputs("Invalid bracket string\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_status == 0) {
        fputs("Failed to read input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!minimum_swaps(input, length, &swaps)) {
        fputs("Invalid bracket string\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", swaps) >= 0) {
        status = EXIT_SUCCESS;
    }

    free(input);
    return status;
}