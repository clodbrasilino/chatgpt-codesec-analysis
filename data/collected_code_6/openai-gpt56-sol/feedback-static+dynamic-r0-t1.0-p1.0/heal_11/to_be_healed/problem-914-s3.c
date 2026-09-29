#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_two_alternating_characters(const char *str, size_t length)
{
    if (str == NULL || length < 2U || str[0] == str[1]) {
        return false;
    }

    for (size_t i = 2U; i < length; ++i) {
        if (str[i] != str[i % 2U]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character;
    int status = EXIT_FAILURE;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (character == '\0') {
            goto cleanup;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length) {
                goto cleanup;
            }

            char *new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length] = (char)(unsigned char)character;
        ++length;
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        goto cleanup;
    }

    if (puts(has_two_alternating_characters(input, length) ? "Yes" : "No") == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}