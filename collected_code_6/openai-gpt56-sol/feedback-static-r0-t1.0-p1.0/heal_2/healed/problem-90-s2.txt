#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    size_t longest = 0;
    size_t current = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (isalnum((unsigned char)ch)) {
            if (current == SIZE_MAX) {
                fprintf(stderr, "Input token is too long.\n");
                return 1;
            }

            ++current;

            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0;
        }
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    if (printf("%zu\n", longest) < 0) {
        fprintf(stderr, "Failed to write output.\n");
        return 1;
    }

    return 0;
}