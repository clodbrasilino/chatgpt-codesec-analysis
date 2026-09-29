#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    size_t longest = 0;
    size_t current = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (isalnum((unsigned char)ch)) {
            if (current == SIZE_MAX) {
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
        return 1;
    }

    if (printf("%zu\n", longest) < 0) {
        return 1;
    }

    return 0;
}