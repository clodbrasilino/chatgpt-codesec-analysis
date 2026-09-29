#include <ctype.h>
#include <stdio.h>

int main(void)
{
    size_t longest = 0U;
    size_t current = 0U;
    int ch;

    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (isalnum((unsigned char)ch)) {
            if (current < SIZE_MAX) {
                ++current;
            }

            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0U;
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