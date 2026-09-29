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
            if (digits == SIZE_MAX) {
                return EXIT_FAILURE;
            }
            ++digits;
        } else if (isalpha(value)) {
            if (letters == SIZE_MAX) {
                return EXIT_FAILURE;
            }
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