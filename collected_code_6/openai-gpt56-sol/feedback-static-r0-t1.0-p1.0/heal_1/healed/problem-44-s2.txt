#include <stdbool.h>
#include <stdio.h>

static bool matches_word_at_start(const char *string, const char *word)
{
    const unsigned char *s;
    const unsigned char *w;

    if (string == NULL || word == NULL || *word == '\0') {
        return false;
    }

    s = (const unsigned char *)string;
    w = (const unsigned char *)word;

    while (*w != '\0') {
        if (*s == '\0' || *s != *w) {
            return false;
        }
        ++s;
        ++w;
    }

    return *s == '\0' ||
           *s == ' ' ||
           *s == '\t' ||
           *s == '\n' ||
           *s == '\r' ||
           *s == '\f' ||
           *s == '\v';
}

int main(int argc, char *argv[])
{
    const char *const *args = (const char *const *)argv;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <word>\n",
                argc > 0 && args[0] != NULL ? args[0] : "program");
        return 1;
    }

    if (matches_word_at_start(args[1], args[2])) {
        puts("Match");
        return 0;
    }

    puts("No match");
    return 2;
}