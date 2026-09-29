#include <ctype.h>
#include <stdio.h>

typedef struct {
    size_t alphabets;
    size_t digits;
    size_t special_characters;
} CharacterCounts;

static void update_count(CharacterCounts *counts, unsigned char character)
{
    if (isalpha(character) != 0) {
        ++counts->alphabets;
    } else if (isdigit(character) != 0) {
        ++counts->digits;
    } else {
        ++counts->special_characters;
    }
}

int main(void)
{
    CharacterCounts counts = {0U, 0U, 0U};
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        update_count(&counts, (unsigned char)character);
    }

    if (ferror(stdin) != 0) {
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