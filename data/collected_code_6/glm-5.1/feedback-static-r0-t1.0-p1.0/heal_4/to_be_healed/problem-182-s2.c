#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void categorize_string(const char *str, size_t len, int *upper, int *lower, int *digit, int *special) {
    *upper = 0;
    *lower = 0;
    *digit = 0;
    *special = 0;
    if (str == NULL) return;
    for (size_t i = 0; i < len; i++) {
        unsigned char c = str[i];
        if (c == '\0') break;
        if (isupper(c)) {
            (*upper)++;
        } else if (islower(c)) {
            (*lower)++;
        } else if (isdigit(c)) {
            (*digit)++;
        } else if (!isalnum(c)) {
            (*special)++;
        }
    }
}

int main(void) {
    char *input = malloc(1024 * sizeof(char));
    if (input == NULL) return EXIT_FAILURE;
    printf("Enter a string: ");
    if (fgets(input, 1024, stdin) == NULL) {
        free(input);
        return EXIT_FAILURE;
    }
    input[strcspn(input, "\n")] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    int upper, lower, digit, special;
    categorize_string(input, len, &upper, &lower, &digit, &special);
    printf("Input: %s\n", input);
    printf("Uppercase: %d\n", upper);
    printf("Lowercase: %d\n", lower);
    printf("Digits: %d\n", digit);
    printf("Special chars: %d\n", special);
    free(input);
    return EXIT_SUCCESS;
}