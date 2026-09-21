#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    size_t digits = 0;
    size_t letters = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        unsigned char value = (unsigned char)character;

        if (isdigit(value)) {
            if (digits == SIZE_MAX) {
                return EXIT_FAILURE;
            }
            ++digits;
        } else if (isalpha(value)) {
            if (letters == SIZE_MAX) {
                return EXIT_FAILURE;
            }
            ++letters;
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (printf("Digits: %zu\nLetters: %zu\n", digits, letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}