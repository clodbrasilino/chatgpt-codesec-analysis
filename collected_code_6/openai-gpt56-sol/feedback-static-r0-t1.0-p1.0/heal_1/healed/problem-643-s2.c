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

int main(int argc, char * const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <word>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return 2;
    }

    if (matches_word(argv[1])) {
        puts("Match");
        return 0;
    }

    puts("No match");
    return 1;
}