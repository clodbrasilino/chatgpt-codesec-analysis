#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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
    size_t longest = 0;
    size_t current = 0;

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (isalnum((unsigned char)ch)) {
            ++current;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0;
        }
    }

    if (printf("%zu\n", longest) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}