#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_vowel(char character)
{
    unsigned char value = (unsigned char)character;
    value = (unsigned char)tolower(value);

    return value == 'a' || value == 'e' || value == 'i' ||
           value == 'o' || value == 'u';
}

static size_t count_characters_with_vowel_neighbors(const char *string)
{
    size_t count = 0;
    size_t length;

    if (string == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(string);

    for (size_t index = 1; index + 1 < length; ++index) {
        if (is_vowel(string[index - 1]) && is_vowel(string[index + 1])) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    while (length > 0 && (line[length - 1] == '\n' || line[length - 1] == '\r')) {
        line[--length] = '\0';
    }

    printf("%zu\n", count_characters_with_vowel_neighbors(line));

    free(line);
    return EXIT_SUCCESS;
}