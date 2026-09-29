#include <stdbool.h>
#include <stddef.h>
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    const char *program_name = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <string> <word>\n", program_name);
        return 1;
    }

    if (matches_word_at_start(argv[1], argv[2])) {
        puts("Match");
        return 0;
    }

    puts("No match");
    return 2;
}