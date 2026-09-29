#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_word(const char *word)
{
    if (word == NULL) {
        return false;
    }

    const size_t length = strlen(word);

    if (length < 3U) {
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

int main(int argc, const char *const argv[])
{
    const char *program_name = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <word>\n", program_name);
        return 2;
    }

    if (matches_word(argv[1])) {
        puts("Match");
        return 0;
    }

    puts("No match");
    return 1;
}