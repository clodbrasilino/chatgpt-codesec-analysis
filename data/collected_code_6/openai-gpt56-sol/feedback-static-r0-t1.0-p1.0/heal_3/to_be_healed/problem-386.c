#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_swaps(const char *str, size_t *result)
{
    size_t open_count = 0;
    size_t close_count = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (const char *p = str; *p != '\0'; ++p) {
        if (*p == '[') {
            ++open_count;

            if (imbalance > 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return -1;
                }

                swaps += imbalance;
                --imbalance;
            }
        } else if (*p == ']') {
            ++close_count;

            if (close_count > open_count) {
                imbalance = close_count - open_count;
            }
        } else {
            return -1;
        }
    }

    if (open_count != close_count) {
        return -1;
    }

    *result = swaps;
    return 0;
}

static int read_line(char **buffer)
{
    size_t length = 0;
    size_t capacity = 64;
    char *data;

    if (buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(data);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2) {
            free(data);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_data;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            if (new_capacity <= capacity) {
                free(data);
                return -1;
            }

            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return -1;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[length++] = (char)ch;
    }

    data[length] = '\0';
    *buffer = data;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t swaps = 0;

    if (read_line(&input) != 0) {
        return EXIT_FAILURE;
    }

    if (minimum_swaps(input, &swaps) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%zu\n", swaps) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}