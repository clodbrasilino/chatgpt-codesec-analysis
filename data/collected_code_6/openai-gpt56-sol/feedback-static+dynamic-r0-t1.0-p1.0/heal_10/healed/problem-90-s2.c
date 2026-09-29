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

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                return -1;
            }
            break;
        }

        if (isalnum((unsigned char)ch)) {
            if (current == SIZE_MAX) {
                return -1;
            }

            ++current;

            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0;
        }
    }

    *result = longest;
    return 0;
}

int main(void)
{
    size_t longest;

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