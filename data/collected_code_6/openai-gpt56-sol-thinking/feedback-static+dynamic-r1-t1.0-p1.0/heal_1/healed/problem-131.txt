#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_vowel(unsigned char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

static void reverse_vowels(char *string)
{
    char *left;
    char *right;

    if (string == NULL || *string == '\0') {
        return;
    }

    left = string;
    right = string;

    while (*right != '\0') {
        ++right;
    }

    --right;

    while (left < right) {
        while (left < right && !is_vowel((unsigned char)*left)) {
            ++left;
        }

        while (left < right && !is_vowel((unsigned char)*right)) {
            --right;
        }

        if (left < right) {
            char temporary = *left;
            *left = *right;
            *right = temporary;
            ++left;
            --right;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        if (fputs("Usage: reverse_vowels <string>\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    reverse_vowels(argv[1]);

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}