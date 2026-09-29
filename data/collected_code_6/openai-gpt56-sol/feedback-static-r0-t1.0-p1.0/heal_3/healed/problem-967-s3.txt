#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_all_vowels(const char *string)
{
    unsigned int found = 0;
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
    char *input;
    size_t length = 0;
    size_t capacity = 128;
    int character;

    if (stream == NULL) {
        return NULL;
    }

    input = malloc(capacity);
    if (input == NULL) {
        return NULL;
    }

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (length == SIZE_MAX - 1) {
            free(input);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                return NULL;
            }

            new_capacity = capacity * 2;
            resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                return NULL;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stream) || (character == EOF && length == 0)) {
        free(input);
        return NULL;
    }

    input[length] = '\0';
    return input;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (puts(contains_all_vowels(input) ? "Accepted" : "Rejected") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}