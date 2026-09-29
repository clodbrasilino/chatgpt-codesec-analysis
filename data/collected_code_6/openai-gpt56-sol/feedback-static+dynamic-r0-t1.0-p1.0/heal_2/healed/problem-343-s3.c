#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t digits = 0;
    size_t letters = 0;
    int character;

    while ((character = getchar()) != EOF) {
        unsigned char value = (unsigned char)character;

        if (isdigit(value)) {
            ++digits;
        } else if (isalpha(value)) {
            ++letters;
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (printf("Digits: %zu\nLetters: %zu\n", digits, letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}