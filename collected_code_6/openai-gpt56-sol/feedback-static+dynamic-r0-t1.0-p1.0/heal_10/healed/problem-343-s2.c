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

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                return -1;
            }
            break;
        }

        if (isdigit((unsigned char)ch)) {
            if (counts->digits == UINTMAX_MAX) {
                return -1;
            }
            counts->digits++;
        } else if (isalpha((unsigned char)ch)) {
            if (counts->letters == UINTMAX_MAX) {
                return -1;
            }
            counts->letters++;
        }
    }

    return 0;
}

int main(void)
{
    CharacterCounts counts;

    if (count_digits_and_letters(stdin, &counts) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Digits: %" PRIuMAX "\nLetters: %" PRIuMAX "\n",
               counts.digits, counts.letters) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}