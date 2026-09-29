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

    if (counts == NULL) {
        return -1;
    }

    counts->digits = 0;
    counts->letters = 0;

    for (;;) {
        const size_t bytes_read = fread(buffer, sizeof buffer[0],
                                        sizeof buffer / sizeof buffer[0],
                                        stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (isdigit((int)buffer[i])) {
                ++counts->digits;
            } else if (isalpha((int)buffer[i])) {
                ++counts->letters;
            }
        }

        if (bytes_read < sizeof buffer / sizeof buffer[0]) {
            if (ferror(stdin)) {
                return -1;
            }
            break;
        }
    }

    return 0;
}

int main(void)
{
    CharacterCounts counts;

    if (count_digits_and_letters(&counts) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("Digits: %zu\nLetters: %zu\n",
               counts.digits, counts.letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}