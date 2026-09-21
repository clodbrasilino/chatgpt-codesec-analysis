#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void categorize_string(const char *str, size_t len, int *upper, int *lower, int *digit, int *special) {
    *upper = 0;
    *lower = 0;
    *digit = 0;
    *special = 0;
    for (size_t i = 0; i < len; i++) {
        unsigned char c = str[i];
        if (isupper(c) != 0) {
            (*upper)++;
        } else if (islower(c) != 0) {
            (*lower)++;
        } else if (isdigit(c) != 0) {
            (*digit)++;
        } else if (!isalnum(c)) {
            (*special)++;
        }
    }
}

int main(void) {
    const char *input = "Hello World! 123 @#$";
    int upper, lower, digit, special;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    categorize_string(input, len, &upper, &lower, &digit, &special);
    printf("Input: %s\n", input);
    printf("Uppercase: %d\n", upper);
    printf("Lowercase: %d\n", lower);
    printf("Digits: %d\n", digit);
    printf("Special chars: %d\n", special);
    return 0;
}