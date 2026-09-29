#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

static bool matches_word(const char *word)
{
    if (word == NULL) {
        return false;
    }

    size_t length = 0U;

    while (word[length] != '\0') {
        if (!isalpha((unsigned char)word[length])) {
            return false;
        }
        ++length;
    }

    if (length < 3U) {
        return false;
    }

    for (size_t i = 1U; i < length - 1U; ++i) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
    }

    return false;
}

int main(int argc, char *const *const argv)
{
    if (argc != 2) {
        const char *program_name = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program_name = argv[0];
        }

        (void)fprintf(stderr, "Usage: %s <word>\n", program_name);
        return 2;
    }

    if (argv == NULL || argv[1] == NULL) {
        (void)fputs("Invalid argument\n", stderr);
        return 2;
    }

    if (matches_word(argv[1])) {
        (void)puts("Match");
        return 0;
    }

    (void)puts("No match");
    return 1;
}