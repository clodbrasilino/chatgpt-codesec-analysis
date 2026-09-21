#include <ctype.h>
#include <stdio.h>

typedef struct {
    size_t alphabets;
    size_t digits;
    size_t special_characters;
} CharacterCounts;

static int count_characters(FILE *stream, CharacterCounts *counts)
{
    int character;

    counts->alphabets = 0U;
    counts->digits = 0U;
    counts->special_characters = 0U;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        unsigned char value = (unsigned char)character;

        if (isalpha(value) != 0) {
            ++counts->alphabets;
        } else if (isdigit(value) != 0) {
            ++counts->digits;
        } else {
            ++counts->special_characters;
        }
    }

    return ferror(stream) == 0;
}

int main(void)
{
    CharacterCounts counts;

    if (!count_characters(stdin, &counts)) {
        return 1;
    }

    if (printf("Alphabets: %zu\n"
               "Digits: %zu\n"
               "Special characters: %zu\n",
               counts.alphabets,
               counts.digits,
               counts.special_characters) < 0) {
        return 1;
    }

    return 0;
}