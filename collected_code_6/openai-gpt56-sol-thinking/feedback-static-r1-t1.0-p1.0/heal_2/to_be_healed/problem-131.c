#include <stdbool.h>
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

static void reverse_vowels(char *string)
{
    size_t left = 0;
    size_t right;

    if (string == NULL) {
        return;
    }

    right = strlen(string);

    while (left < right) {
        while (left < right &&
               !is_vowel((unsigned char)string[left])) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *string;
    size_t length;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    length = strlen(argv[1]);
    string = malloc(length + 1);

    if (string == NULL) {
        fputs("Memory allocation failed.\n", stderr);
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