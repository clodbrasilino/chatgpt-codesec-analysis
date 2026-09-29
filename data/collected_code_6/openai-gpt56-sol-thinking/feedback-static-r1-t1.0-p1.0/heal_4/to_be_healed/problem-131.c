#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_vowel(unsigned char character)
{
    return character == 'a' || character == 'e' ||
           character == 'i' || character == 'o' ||
           character == 'u' || character == 'A' ||
           character == 'E' || character == 'I' ||
           character == 'O' || character == 'U';
}

static bool duplicate_argument(const char *source, char **destination,
                               size_t *length)
{
    size_t capacity = 64;
    size_t used = 0;
    char *copy;

    if (source == NULL || destination == NULL || length == NULL) {
        return false;
    }

    copy = malloc(capacity);
    if (copy == NULL) {
        return false;
    }

    while (source[used] != '\0') {
        if (used == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(copy);
                return false;
            }

            new_capacity = capacity * 2;
            resized = realloc(copy, new_capacity);
            if (resized == NULL) {
                free(copy);
                return false;
            }

            copy = resized;
            capacity = new_capacity;
        }

        copy[used] = source[used];
        ++used;
    }

    copy[used] = '\0';
    *destination = copy;
    *length = used;
    return true;
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
    /* Possible weaknesses found:
     *  The scope of the variable 'program_name' can be reduced. [variableScope]
     */
    const char *program_name;
    char *string;
    size_t length;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        program_name = argv != NULL && argc > 0 && argv[0] != NULL
                           ? argv[0]
                           : "program";

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    if (!duplicate_argument(argv[1], &string, &length)) {
        fputs("Memory allocation failed.\n", stderr);
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