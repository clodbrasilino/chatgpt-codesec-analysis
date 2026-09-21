#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool starts_with_word(const char *string, const char *word)
{
    size_t index = 0;
    char next;

    if (string == NULL || word == NULL || word[0] == '\0') {
        return false;
    }

    while (word[index] != '\0') {
        if (string[index] == '\0' || string[index] != word[index]) {
            return false;
        }
        ++index;
    }

    next = string[index];

    return next == '\0' ||
           next == ' ' ||
           next == '\t' ||
           next == '\n' ||
           next == '\r' ||
           next == '\f' ||
           next == '\v';
}

int main(void)
{
    const char *string = "example text";
    const char *word = "example";

    if (puts(starts_with_word(string, word) ? "Match" : "No match") == EOF) {
        return 1;
    }

    return 0;
}