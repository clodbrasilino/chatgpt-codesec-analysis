#include <ctype.h>
#include <stdio.h>

int main(void)
{
    size_t digits = 0U;
    size_t letters = 0U;
    int character;

    while ((character = fgetc(stdin)) != EOF) {
        unsigned char value = (unsigned char)character;

        if (isdigit(value) != 0) {
            ++digits;
        } else if (isalpha(value) != 0) {
            ++letters;
        }
    }

    if (ferror(stdin) != 0) {
        return 1;
    }

    if (printf("Digits: %zu\nLetters: %zu\n", digits, letters) < 0) {
        return 1;
    }

    return 0;
}