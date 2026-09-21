#include <stdbool.h>
#include <stdio.h>

static bool matches_word_at_start(const char *string, const char *word)
{
    size_t index = 0;

    if (string == NULL || word == NULL || word[0] == '\0') {
        return false;
    }

    while (word[index] != '\0') {
        if (string[index] == '\0' || string[index] != word[index]) {
            return false;
        }
        ++index;
    }

    return string[index] == '\0' ||
           string[index] == ' ' ||
           string[index] == '\t' ||
           string[index] == '\n' ||
           string[index] == '\r' ||
           string[index] == '\f' ||
           string[index] == '\v';
}

int main(int argc, const char *const argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <word>\n", argv[0]);
        return 1;
    }

    if (matches_word_at_start(argv[1], argv[2])) {
        puts("Match");
        return 0;
    }

    puts("No match");
    return 2;
}