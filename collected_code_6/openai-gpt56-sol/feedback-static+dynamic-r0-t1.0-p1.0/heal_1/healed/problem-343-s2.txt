#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t digits;
    size_t letters;
} CharacterCounts;

static int count_digits_and_letters(CharacterCounts *counts)
{
    unsigned char buffer[4096];
    size_t bytes_read;

    if (counts == NULL) {
        return -1;
    }

    counts->digits = 0;
    counts->letters = 0;

    while ((bytes_read = fread(buffer, 1, sizeof buffer, stdin)) != 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            if (isdigit(buffer[i]) != 0) {
                ++counts->digits;
            } else if (isalpha(buffer[i]) != 0) {
                ++counts->letters;
            }
        }
    }

    return ferror(stdin) != 0 ? -1 : 0;
}

int main(void)
{
    CharacterCounts counts;

    if (count_digits_and_letters(&counts) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("Digits: %zu\nLetters: %zu\n",
               counts.digits,
               counts.letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}