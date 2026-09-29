#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void count_characters(const char *str, int *alphabets, int *digits, int *special_chars) {
    if (str == NULL || alphabets == NULL || digits == NULL || special_chars == NULL) {
        return;
    }

    *alphabets = 0;
    *digits = 0;
    *special_chars = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isalpha(c)) {
            (*alphabets)++;
        } else if (isdigit(c)) {
            (*digits)++;
        } else {
            (*special_chars)++;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    int alphabets = 0, digits = 0, special_chars = 0;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    str[strcspn(str, "\n")] = '\0';

    count_characters(str, &alphabets, &digits, &special_chars);

    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special Characters: %d\n", special_chars);

    return 0;
}