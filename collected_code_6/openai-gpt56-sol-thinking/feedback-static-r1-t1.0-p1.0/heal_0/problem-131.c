#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_vowel(unsigned char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

static void reverse_vowels(char *string)
{
    size_t left;
    size_t right;

    if (string == NULL) {
        return;
    }

    left = 0;
    right = strlen(string);

    while (left < right) {
        while (left < right && !is_vowel((unsigned char)string[left])) {
            ++left;
        }

        while (left < right) {
            --right;
            if (is_vowel((unsigned char)string[right])) {
                break;
            }
        }

        if (left < right) {
            char temporary = string[left];
            string[left] = string[right];
            string[right] = temporary;
            ++left;
        }
    }
}

int main(int argc, char *argv[])
{
    char *string;
    size_t length;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    length = strlen(argv[1]);
    string = malloc(length + 1);

    if (string == NULL) {
        if (fputs("Memory allocation failed.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    memcpy(string, argv[1], length + 1);
    reverse_vowels(string);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}