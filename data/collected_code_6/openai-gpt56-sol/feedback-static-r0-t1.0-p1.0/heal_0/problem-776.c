#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int is_vowel(unsigned char c)
{
    c = (unsigned char)tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

static size_t count_characters_between_vowels(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    for (size_t i = 1; string[i] != '\0' && string[i + 1] != '\0'; ++i) {
        if (is_vowel((unsigned char)string[i - 1]) &&
            is_vowel((unsigned char)string[i + 1])) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    while (length > 0 && (line[length - 1] == '\n' || line[length - 1] == '\r')) {
        line[--length] = '\0';
    }

    printf("%zu\n", count_characters_between_vowels(line));

    free(line);
    return EXIT_SUCCESS;
}