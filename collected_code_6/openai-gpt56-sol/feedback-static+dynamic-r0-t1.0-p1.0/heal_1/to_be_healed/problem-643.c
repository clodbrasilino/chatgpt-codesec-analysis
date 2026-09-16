#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_word(const char *word)
{
    size_t length;

    if (word == NULL) {
        return false;
    }

    length = strlen(word);
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <word>\n", argv[0]);
        return 2;
    }

    if (matches_word(argv[1])) {
        (void)puts("Match");
        return 0;
    }

    (void)puts("No match");
    return 1;
}