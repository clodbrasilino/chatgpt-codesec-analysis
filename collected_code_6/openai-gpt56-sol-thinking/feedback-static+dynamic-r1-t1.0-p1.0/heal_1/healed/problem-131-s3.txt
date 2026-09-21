#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH ((size_t)1048576)

static bool is_vowel(char character)
{
    switch (character) {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
    }
}

static bool bounded_string_length(const char *string, size_t limit,
                                  size_t *length)
{
    size_t index;

    if (string == NULL || length == NULL) {
        return false;
    }

    for (index = 0; index < limit; ++index) {
        if (string[index] == '\0') {
            *length = index;
            return true;
        }
    }

    return false;
}

static bool reverse_vowels(char *string, size_t length)
{
    size_t left = 0;
    size_t right = length;

    if (string == NULL) {
        return false;
    }

    while (left < right) {
        while (left < right && !is_vowel(string[left])) {
            ++left;
        }

        while (left < right && !is_vowel(string[right - 1])) {
            --right;
        }

        if (left < right) {
            char temporary = string[left];
            string[left] = string[right - 1];
            string[right - 1] = temporary;
            ++left;
            --right;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    size_t length;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    if (!bounded_string_length(argv[1], MAX_STRING_LENGTH + 1, &length)) {
        fprintf(stderr, "Input exceeds the maximum supported length.\n");
        return EXIT_FAILURE;
    }

    if (!reverse_vowels(argv[1], length)) {
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}