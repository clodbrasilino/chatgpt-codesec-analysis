#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool starts_with_word(const char *string, const char *word)
{
    size_t word_length;

    if (string == NULL || word == NULL || word[0] == '\0') {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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

int main(void)
{
    const char *string = "example text";
    const char *word = "example";

    if (starts_with_word(string, word)) {
        if (puts("Match") == EOF) {
            return 1;
        }
    } else {
        if (puts("No match") == EOF) {
            return 1;
        }
    }

    return 0;
}