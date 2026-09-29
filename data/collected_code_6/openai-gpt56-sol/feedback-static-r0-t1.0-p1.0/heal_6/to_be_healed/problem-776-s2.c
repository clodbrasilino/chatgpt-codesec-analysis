#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int is_vowel(unsigned char character)
{
    character = (unsigned char)tolower(character);

    return character == 'a' || character == 'e' ||
           character == 'i' || character == 'o' ||
           character == 'u';
}

static size_t count_characters_with_vowel_neighbors(const char *string,
                                                     size_t length)
{
    size_t count = 0;

    if (string == NULL || length < 3) {
        return 0;
    }

    for (size_t i = 1; i < length - 1; ++i) {
        if (is_vowel((unsigned char)string[i - 1]) &&
            is_vowel((unsigned char)string[i + 1])) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };

    char *input = malloc((size_t)MAX_INPUT_LENGTH);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0;
    int character;

    while (length < (size_t)MAX_INPUT_LENGTH &&
           /* Possible weaknesses found:
            * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
            */
           (character = getchar()) != EOF &&
           character != '\n') {
        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == (size_t)MAX_INPUT_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();

        if (character != EOF && character != '\n') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((character = getchar()) != EOF && character != '\n') {
            }

            free(input);
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (printf("%zu\n",
               count_characters_with_vowel_neighbors(input, length)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}