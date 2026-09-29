#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_first_longest_even_word(const char *text)
{
    const unsigned char *current;
    const unsigned char *best_start = NULL;
    size_t best_length = 0;

    if (text == NULL) {
        return NULL;
    }

    current = (const unsigned char *)text;

    while (*current != '\0') {
        const unsigned char *start;
        size_t length;

        while (*current != '\0' && isspace((unsigned char)*current)) {
            ++current;
        }

        start = current;

        while (*current != '\0' && !isspace((unsigned char)*current)) {
            ++current;
        }

        length = (size_t)(current - start);

        if (length != 0 && length % 2 == 0 && length > best_length) {
            best_start = start;
            best_length = length;
        }
    }

    if (best_start == NULL || best_length > SIZE_MAX - 1) {
        return NULL;
    }

    char *result = malloc(best_length + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, best_start, best_length);
    result[best_length] = '\0';

    return result;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        if (character == '\0') {
            free(input);
            fputs("Input contains a null character.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length >= SIZE_MAX - 1) {
            free(input);
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    char *word = find_first_longest_even_word(input);
    free(input);

    if (word == NULL) {
        puts("No even-length word found.");
        return EXIT_SUCCESS;
    }

    puts(word);
    free(word);

    return EXIT_SUCCESS;
}