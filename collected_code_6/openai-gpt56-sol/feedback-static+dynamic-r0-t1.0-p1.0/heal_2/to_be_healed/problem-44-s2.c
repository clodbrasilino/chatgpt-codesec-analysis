#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool matches_word_at_start(const char *string, const char *word)
{
    size_t word_length;

    if (string == NULL || word == NULL || word[0] == '\0') {
        return false;
    }

    word_length = strlen(word);

    return strncmp(string, word, word_length) == 0 &&
           (string[word_length] == '\0' ||
            string[word_length] == ' ' ||
            string[word_length] == '\t' ||
            string[word_length] == '\n' ||
            string[word_length] == '\r' ||
            string[word_length] == '\f' ||
            string[word_length] == '\v');
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
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