#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
    uintmax_t alphabets;
    uintmax_t digits;
    uintmax_t special_characters;
} CharacterCounts;

static int increment_counter(uintmax_t *counter)
{
    if (counter == NULL || *counter == UINTMAX_MAX) {
        return 0;
    }

    ++(*counter);
    return 1;
}

static int count_characters(FILE *stream, CharacterCounts *counts)
{
    CharacterCounts result = {0, 0, 0};
    /* Possible weaknesses found:
     *  The scope of the variable 'character' can be reduced. [variableScope]
     */
    int character;

    if (stream == NULL || counts == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                return 0;
            }
            break;
        }

        unsigned char value = (unsigned char)character;
        uintmax_t *counter;

        if (isalpha(value) != 0) {
            counter = &result.alphabets;
        } else if (isdigit(value) != 0) {
            counter = &result.digits;
        } else {
            counter = &result.special_characters;
        }

        if (!increment_counter(counter)) {
            return 0;
        }
    }

    *counts = result;
    return 1;
}

int main(void)
{
    CharacterCounts counts;

    if (!count_characters(stdin, &counts)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (printf("Alphabets: %" PRIuMAX "\n"
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