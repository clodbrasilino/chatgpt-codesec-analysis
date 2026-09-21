#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uintmax_t digits;
    uintmax_t letters;
} CharacterCounts;

static int count_digits_and_letters(CharacterCounts *counts)
{
    int ch;

    if (counts == NULL) {
        return -1;
    }

    counts->digits = 0;
    counts->letters = 0;

    while ((ch = fgetc(stdin)) != EOF) {
        unsigned char c = (unsigned char)ch;

        if (isdigit(c)) {
            if (counts->digits == UINTMAX_MAX) {
                return -1;
            }
            ++counts->digits;
        } else if (isalpha(c)) {
            if (counts->letters == UINTMAX_MAX) {
                return -1;
            }
            ++counts->letters;
        }
    }

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    CharacterCounts counts;

    if (count_digits_and_letters(&counts) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("Digits: %ju\nLetters: %ju\n",
               counts.digits, counts.letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}