#include <ctype.h>
#include <stdio.h>

size_t longest_word_length(const char *text)
{
    size_t longest = 0;
    size_t current = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        unsigned char ch = (unsigned char)*text++;

        if (isalnum(ch)) {
            ++current;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0;
        }
    }

    return longest;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return 1;
        }

        puts("0");
        return 0;
    }

    printf("%zu\n", longest_word_length(input));
    return 0;
}