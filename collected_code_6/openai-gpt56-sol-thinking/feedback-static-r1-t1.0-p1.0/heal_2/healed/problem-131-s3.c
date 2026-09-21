#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

static bool reverse_vowels(char *string)
{
    char *left;
    char *right;

    if (string == NULL) {
        return false;
    }

    left = string;
    right = string;

    while (*right != '\0') {
        ++right;
    }

    while (left < right) {
        while (left < right && !is_vowel(*left)) {
            ++left;
        }

        while (left < right && !is_vowel(*(right - 1))) {
            --right;
        }

        if (left < right) {
            char temporary = *left;
            *left = *(right - 1);
            *(right - 1) = temporary;
            ++left;
            --right;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (!reverse_vowels(argv[1])) {
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}