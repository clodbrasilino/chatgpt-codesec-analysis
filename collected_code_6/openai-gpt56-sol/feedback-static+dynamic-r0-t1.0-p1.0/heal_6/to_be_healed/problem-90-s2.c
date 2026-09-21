#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

int longest_word_length_stream(FILE *stream, size_t *result)
{
    size_t longest = 0;
    size_t current = 0;
    int ch;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF) {
        unsigned char c = (unsigned char)ch;

        if (isalnum(c)) {
            if (current == SIZE_MAX) {
                return -1;
            }

            current++;

            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0;
        }
    }

    if (ferror(stream)) {
        return -1;
    }

    *result = longest;
    return 0;
}

int main(void)
{
    size_t longest = 0;

    if (longest_word_length_stream(stdin, &longest) != 0) {
        fputs("Failed to read input or input word is too long.\n", stderr);
        return 1;
    }

    if (printf("%zu\n", longest) < 0) {
        fputs("Failed to write output.\n", stderr);
        return 1;
    }

    return 0;
}