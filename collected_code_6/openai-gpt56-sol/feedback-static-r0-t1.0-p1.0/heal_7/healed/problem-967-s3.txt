#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_all_vowels(const char *string)
{
    unsigned int found = 0U;
    const unsigned int all_vowels = 0x1FU;

    if (string == NULL) {
        return false;
    }

    while (*string != '\0') {
        switch (tolower((unsigned char)*string)) {
        case 'a':
            found |= 1U << 0;
            break;
        case 'e':
            found |= 1U << 1;
            break;
        case 'i':
            found |= 1U << 2;
            break;
        case 'o':
            found |= 1U << 3;
            break;
        case 'u':
            found |= 1U << 4;
            break;
        default:
            break;
        }

        if (found == all_vowels) {
            return true;
        }

        ++string;
    }

    return false;
}

static char *read_line(FILE *stream)
{
    size_t length = 0U;
    size_t capacity = 128U;
    char *input;

    if (stream == NULL) {
        return NULL;
    }

    input = malloc(capacity);
    if (input == NULL) {
        return NULL;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stream) != 0 || length == 0U) {
                free(input);
                return NULL;
            }
            break;
        }

        if (length == capacity - 1U) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return NULL;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return NULL;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length] = (char)character;
        ++length;
    }

    input[length] = '\0';
    return input;
}

int main(void)
{
    char *input;
    int result;

    input = read_line(stdin);
    if (input == NULL) {
        return ferror(stdin) != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    result = puts(contains_all_vowels(input) ? "Accepted" : "Rejected");
    free(input);

    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}