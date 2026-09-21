#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct char_counts {
    size_t alphabets;
    size_t digits;
    size_t specials;
};

static void count_characters(const char *str, struct char_counts *counts)
{
    size_t i;

    counts->alphabets = 0;
    counts->digits = 0;
    counts->specials = 0;

    if (str == NULL) {
        return;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];

        if (isalpha(c)) {
            counts->alphabets++;
        } else if (isdigit(c)) {
            counts->digits++;
        } else if (!isspace(c)) {
            counts->specials++;
        }
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    struct char_counts counts;
    size_t len;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    count_characters(buffer, &counts);

    printf("Alphabets: %zu\n", counts.alphabets);
    printf("Digits: %zu\n", counts.digits);
    printf("Special characters: %zu\n", counts.specials);

    return EXIT_SUCCESS;
}