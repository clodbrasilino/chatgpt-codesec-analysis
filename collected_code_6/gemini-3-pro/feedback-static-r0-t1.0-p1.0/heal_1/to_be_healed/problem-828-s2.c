#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void count_characters(const char *str, int *alphabets, int *digits, int *specials) {
    if (str == NULL || alphabets == NULL || digits == NULL || specials == NULL) {
        return;
    }

    *alphabets = 0;
    *digits = 0;
    *specials = 0;

    while (*str) {
        if (isalpha((unsigned char)*str)) {
            (*alphabets)++;
        } else if (isdigit((unsigned char)*str)) {
            (*digits)++;
        } else if (!isspace((unsigned char)*str)) {
            (*specials)++;
        }
        str++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    int alphabets = 0;
    int digits = 0;
    int specials = 0;

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        count_characters(buffer, &alphabets, &digits, &specials);

        printf("Alphabets: %d\n", alphabets);
        printf("Digits: %d\n", digits);
        printf("Special characters: %d\n", specials);
    }

    return 0;
}