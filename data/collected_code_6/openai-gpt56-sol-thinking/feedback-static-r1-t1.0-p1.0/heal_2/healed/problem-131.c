#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_vowel(unsigned char character)
{
    return character == 'a' || character == 'e' ||
           character == 'i' || character == 'o' ||
           character == 'u' || character == 'A' ||
           character == 'E' || character == 'I' ||
           character == 'O' || character == 'U';
}

static char *duplicate_string(const char *source, size_t length)
{
    char *destination;
    size_t index;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    destination = malloc(length + 1);
    if (destination == NULL) {
        return NULL;
    }

    for (index = 0; index < length; ++index) {
        destination[index] = source[index];
    }

    destination[length] = '\0';
    return destination;
}

static void reverse_vowels(char *string, size_t length)
{
    size_t left = 0;
    size_t right = length;

    if (string == NULL) {
        return;
    }

    while (left < right) {
        while (left < right &&
               !is_vowel((unsigned char)string[left])) {
            ++left;
        }

        while (left < right &&
               !is_vowel((unsigned char)string[right - 1])) {
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
}

int main(int argc, char **argv)
{
    size_t length;
    char *string;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name =
            argv != NULL && argc > 0 && argv[0] != NULL
                ? argv[0]
                : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    length = strlen(argv[1]);
    string = duplicate_string(argv[1], length);

    if (string == NULL) {
        if (fputs("Memory allocation failed.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    reverse_vowels(string, length);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}