#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int minimum_swaps(const char *str, size_t length, size_t *result)
{
    size_t open_count = 0;
    size_t close_count = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (result == NULL || (str == NULL && length != 0)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == '[') {
            if (open_count == SIZE_MAX) {
                return -1;
            }

            ++open_count;

            if (imbalance != 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return -1;
                }

                swaps += imbalance;
                --imbalance;
            }
        } else if (str[i] == ']') {
            if (close_count == SIZE_MAX) {
                return -1;
            }

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

static int read_input(char **buffer, size_t *length)
{
    size_t capacity = 256;
    size_t used = 0;
    char *input;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    input = malloc(capacity);
    if (input == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char chunk[256];

        if (fgets(chunk, sizeof chunk, stdin) == NULL) {
            if (ferror(stdin)) {
                free(input);
                return -1;
            }
            break;
        }

        size_t i = 0;

        while (i < sizeof chunk && chunk[i] != '\0') {
            unsigned char character = (unsigned char)chunk[i++];

            if (character == '\n') {
                *buffer = input;
                *length = used;
                return 0;
            }

            if (character == '\r') {
                if (chunk[i] == '\n') {
                    /* Possible weaknesses found:
                     *  Variable 'i' is assigned a value that is never used. [unreadVariable]
                     */
                    ++i;
                } else if (chunk[i] == '\0') {
                    /* Possible weaknesses found:
                     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    int next_character = fgetc(stdin);

                    if (next_character != '\n' && next_character != EOF) {
                        if (ungetc(next_character, stdin) == EOF) {
                            free(input);
                            return -1;
                        }
                    } else if (next_character == EOF && ferror(stdin)) {
                        free(input);
                        return -1;
                    }
                }

                *buffer = input;
                *length = used;
                return 0;
            }

            if (character != '[' && character != ']') {
                free(input);
                return -1;
            }

            if (used == capacity) {
                size_t new_capacity;
                char *new_input;

                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return -1;
                }

                new_capacity = capacity * 2;
                new_input = realloc(input, new_capacity);
                if (new_input == NULL) {
                    free(input);
                    return -1;
                }

                input = new_input;
                capacity = new_capacity;
            }

            input[used++] = (char)character;
        }
    }

    *buffer = input;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t swaps = 0;
    int status = EXIT_FAILURE;

    if (read_input(&input, &length) != 0) {
        goto cleanup;
    }

    if (minimum_swaps(input, length, &swaps) != 0) {
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