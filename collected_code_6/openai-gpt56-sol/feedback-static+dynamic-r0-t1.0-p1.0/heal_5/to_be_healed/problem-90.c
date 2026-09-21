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
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (isalnum((unsigned char)ch)) {
            ++current;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0;
        }
    }

    if (ch == EOF && ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", longest) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}