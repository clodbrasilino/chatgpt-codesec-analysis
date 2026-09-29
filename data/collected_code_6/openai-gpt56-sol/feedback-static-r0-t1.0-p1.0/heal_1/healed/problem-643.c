#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool matches_word(const char *word, size_t length)
{
    if (word == NULL || length < 3U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (!isalpha((unsigned char)word[i])) {
            return false;
        }
    }

    for (size_t i = 1U; i + 1U < length; ++i) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    const char *word;
    size_t length = 0U;

    program_name = (argc > 0 && argv != NULL && argv[0] != NULL)
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        (void)fprintf(stderr, "Usage: %s <word>\n", program_name);
        return 2;
    }

    word = argv[1];

    while (word[length] != '\0') {
        ++length;
    }

    if (matches_word(word, length)) {
        (void)puts("Match");
        return 0;
    }

    (void)puts("No match");
    return 1;
}