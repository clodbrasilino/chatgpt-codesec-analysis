#include <ctype.h>
#include <stdio.h>

size_t longest_word_length_stream(FILE *stream)
{
    size_t longest = 0;
    size_t current = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF) {
        if (isalnum((unsigned char)ch)) {
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
    size_t longest = longest_word_length_stream(stdin);

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    printf("%zu\n", longest);
    return 0;
}