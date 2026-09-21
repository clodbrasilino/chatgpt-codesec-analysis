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
        if (isalnum((unsigned char)*text)) {
            ++current;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0;
        }
        ++text;
    }

    return longest;
}

int main(void)
{
    size_t longest = 0;
    size_t current = 0;
    int ch;

    while ((ch = getchar()) != EOF) {
        if (isalnum((unsigned char)ch)) {
            ++current;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0;
        }

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    printf("%zu\n", longest);
    return 0;
}