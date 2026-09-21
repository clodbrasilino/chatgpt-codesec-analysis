#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int is_vowel(char character)
{
    unsigned char value = (unsigned char)character;
    value = (unsigned char)tolower(value);

    return value == 'a' || value == 'e' || value == 'i' ||
           value == 'o' || value == 'u';
}

static size_t count_characters_with_vowel_neighbors(const char *string,
                                                     size_t length)
{
    size_t count = 0;

    if (string == NULL || length < 3) {
        return 0;
    }

    for (size_t index = 1; index < length - 1; ++index) {
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
    ssize_t input_length = getline(&line, &capacity, stdin);

    if (input_length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    size_t length = (size_t)input_length;

    while (length > 0 &&
           (line[length - 1] == '\n' || line[length - 1] == '\r')) {
        --length;
    }

    printf("%zu\n", count_characters_with_vowel_neighbors(line, length));

    free(line);
    return EXIT_SUCCESS;
}