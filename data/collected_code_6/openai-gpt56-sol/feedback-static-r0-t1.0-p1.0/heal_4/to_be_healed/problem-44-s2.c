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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *const argv[const])
{
    if (argc != 3) {
        fprintf(stderr,
                "Usage: %s <string> <word>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return 1;
    }

    if (matches_word_at_start(argv[1], argv[2])) {
        puts("Match");
        return 0;
    }

    puts("No match");
    return 2;
}