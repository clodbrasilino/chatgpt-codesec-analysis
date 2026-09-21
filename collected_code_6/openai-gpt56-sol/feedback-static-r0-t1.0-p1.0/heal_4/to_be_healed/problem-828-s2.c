#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uintmax_t alphabets;
    uintmax_t digits;
    uintmax_t special_characters;
} CharacterCounts;

static int count_characters(FILE *stream, CharacterCounts *counts)
{
    int character;

    if (stream == NULL || counts == NULL) {
        return 0;
    }

    *counts = (CharacterCounts){0, 0, 0};

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        uintmax_t *counter;
        const unsigned char value = (unsigned char)character;

        if (isalpha(value)) {
            counter = &counts->alphabets;
        } else if (isdigit(value)) {
            counter = &counts->digits;
        } else {
            counter = &counts->special_characters;
        }

        if (*counter == UINTMAX_MAX) {
            return 0;
        }

        ++*counter;
    }

    return ferror(stream) == 0;
}

int main(void)
{
    CharacterCounts counts;

    if (!count_characters(stdin, &counts)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (printf(
            "Alphabets: %" PRIuMAX "\n"
            "Digits: %" PRIuMAX "\n"
            "Special characters: %" PRIuMAX "\n",
            counts.alphabets,
            counts.digits,
            counts.special_characters) < 0) {
        fputs("Failed to write output.\n", stderr);
        return 1;
    }

    return 0;
}