#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uintmax_t digits;
    uintmax_t letters;
} CharacterCounts;

static int count_digits_and_letters(FILE *stream, CharacterCounts *counts)
{
    int ch;

    if (stream == NULL || counts == NULL) {
        return -1;
    }

    counts->digits = 0;
    counts->letters = 0;

    while ((ch = fgetc(stream)) != EOF) {
        unsigned char c = (unsigned char)ch;

        if (isdigit(c) != 0) {
            if (counts->digits == UINTMAX_MAX) {
                return -1;
            }
            ++counts->digits;
        } else if (isalpha(c) != 0) {
            if (counts->letters == UINTMAX_MAX) {
                return -1;
            }
            ++counts->letters;
        }
    }

    return ferror(stream) != 0 ? -1 : 0;
}

int main(void)
{
    CharacterCounts counts;

    if (count_digits_and_letters(stdin, &counts) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("Digits: %" PRIuMAX "\nLetters: %" PRIuMAX "\n",
               counts.digits, counts.letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}