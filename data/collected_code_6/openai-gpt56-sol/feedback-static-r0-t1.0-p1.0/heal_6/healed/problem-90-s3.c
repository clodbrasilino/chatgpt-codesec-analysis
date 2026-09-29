#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t longest_word_length(const char *text)
{
    size_t longest = 0U;
    size_t current = 0U;

    if (text == NULL) {
        return 0U;
    }

    while (*text != '\0') {
        if (isalnum((unsigned char)*text) != 0) {
            ++current;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0U;
        }
        ++text;
    }

    return longest;
}

int main(void)
{
    char *input;
    size_t capacity = 128U;
    size_t length = 0U;
    int status = EXIT_FAILURE;
    int ch;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1U) {
            goto cleanup;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length + 1U) {
                goto cleanup;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin) != 0) {
        goto cleanup;
    }

    input[length] = '\0';

    if (printf("%zu\n", longest_word_length(input)) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}