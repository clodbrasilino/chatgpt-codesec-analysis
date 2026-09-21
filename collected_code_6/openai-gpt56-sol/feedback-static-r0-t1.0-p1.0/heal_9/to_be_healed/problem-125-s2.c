#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static int max_zero_one_difference(const char *string, size_t length,
                                   size_t *start, size_t *end)
{
    int current = 0;
    int maximum = 0;
    size_t current_start = 0;

    if (string == NULL || start == NULL || end == NULL ||
        length == 0 || length > (size_t)INT_MAX) {
        return -1;
    }

    *start = 0;
    *end = 0;

    for (size_t i = 0; i < length; ++i) {
        int value;

        if (string[i] == '0') {
            value = 1;
        } else if (string[i] == '1') {
            value = -1;
        } else {
            return -1;
        }

        if (current < 0) {
            current = value;
            current_start = i;
        } else {
            current += value;
        }

        if (current > maximum) {
            maximum = current;
            *start = current_start;
            *end = i;
        }
    }

    return maximum;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int status = EXIT_FAILURE;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    int done = 0;

    while (!done && fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t i = 0;

        while (buffer[i] != '\0') {
            unsigned char character = (unsigned char)buffer[i++];

            if (character == '\n') {
                done = 1;
                break;
            }

            if (character == '\r') {
                if (buffer[i] == '\n') {
                    /* Possible weaknesses found:
                     *  Variable 'i' is assigned a value that is never used. [unreadVariable]
                     */
                    ++i;
                } else if (buffer[i] == '\0') {
                    /* Possible weaknesses found:
                     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    int next = fgetc(stdin);

                    if (next != '\n' && next != EOF) {
                        if (ungetc(next, stdin) == EOF) {
                            goto cleanup;
                        }
                    } else if (next == EOF && ferror(stdin)) {
                        goto cleanup;
                    }
                }

                done = 1;
                break;
            }

            if (character != '0' && character != '1') {
                goto cleanup;
            }

            if (length >= (size_t)INT_MAX) {
                goto cleanup;
            }

            if (length == capacity) {
                size_t new_capacity = capacity == 0 ? 64 : capacity * 2;

                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }

                if (new_capacity > (size_t)INT_MAX) {
                    new_capacity = (size_t)INT_MAX;
                }

                if (new_capacity <= capacity ||
                    new_capacity > SIZE_MAX / sizeof *input) {
                    goto cleanup;
                }

                char *new_input = realloc(input,
                                          new_capacity * sizeof *input);
                if (new_input == NULL) {
                    goto cleanup;
                }

                input = new_input;
                capacity = new_capacity;
            }

            input[length++] = (char)character;
        }
    }

    if (ferror(stdin) || length == 0) {
        goto cleanup;
    }

    size_t start;
    size_t end;
    int result = max_zero_one_difference(input, length, &start, &end);

    if (result < 0 || printf("%d\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}