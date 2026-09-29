#include <ctype.h>
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

    counts->alphabets = 0;
    counts->digits = 0;
    counts->special_characters = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        const unsigned char value = (unsigned char)character;

        if (isalpha(value)) {
            if (counts->alphabets == UINTMAX_MAX) {
                return 0;
            }
            ++counts->alphabets;
        } else if (isdigit(value)) {
            if (counts->digits == UINTMAX_MAX) {
                return 0;
            }
            ++counts->digits;
        } else {
            if (counts->special_characters == UINTMAX_MAX) {
                return 0;
            }
            ++counts->special_characters;
        }
    }

    return !ferror(stream);
}

int main(void)
{
    CharacterCounts counts;

    if (!count_characters(stdin, &counts)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (printf("Alphabets: %ju\n"
               "Digits: %ju\n"
               "Special characters: %ju\n",
               counts.alphabets,
               counts.digits,
               counts.special_characters) < 0) {
        return 1;
    }

    return 0;
}