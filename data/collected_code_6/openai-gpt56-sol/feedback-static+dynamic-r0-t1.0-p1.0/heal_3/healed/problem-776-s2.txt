#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

static int is_vowel(unsigned char c)
{
    c = (unsigned char)tolower((int)c);
    return c == 'a' || c == 'e' || c == 'i' ||
           c == 'o' || c == 'u';
}

static size_t count_characters_with_vowel_neighbors(const char *string,
                                                     size_t length)
{
    size_t count = 0;

    if (string == NULL || length < 3) {
        return 0;
    }

    for (size_t i = 1; i < length - 1; ++i) {
        if (is_vowel((unsigned char)string[i - 1]) &&
            is_vowel((unsigned char)string[i + 1])) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;
    int status = EXIT_FAILURE;

    while ((character = getchar()) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length) {
                goto cleanup;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                goto cleanup;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        goto cleanup;
    }

    if (printf("%zu\n",
               count_characters_with_vowel_neighbors(input, length)) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}