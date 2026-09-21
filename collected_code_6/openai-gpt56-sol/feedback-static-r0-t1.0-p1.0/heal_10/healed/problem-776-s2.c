#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int is_vowel(unsigned char character)
{
    character = (unsigned char)tolower((int)character);

    return character == (unsigned char)'a' ||
           character == (unsigned char)'e' ||
           character == (unsigned char)'i' ||
           character == (unsigned char)'o' ||
           character == (unsigned char)'u';
}

static size_t count_characters_with_vowel_neighbors(const char *string,
                                                    size_t length)
{
    size_t count = 0;

    if (string == NULL || length < 3U) {
        return 0U;
    }

    for (size_t i = 1U; i + 1U < length; ++i) {
        if (is_vowel((unsigned char)string[i - 1U]) &&
            is_vowel((unsigned char)string[i + 1U])) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 1024 * 1024 };
    char *input = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    size_t length = 0U;
    int character = EOF;
    int too_long = 0;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length < (size_t)MAX_INPUT_LENGTH) {
            input[length++] = (char)(unsigned char)character;
        } else {
            too_long = 1;
        }
    }

    if (ferror(stdin) || too_long) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (printf("%zu\n",
               count_characters_with_vowel_neighbors(input, length)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}