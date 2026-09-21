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
    const char *input = "Hello World! 123 @#$";
    if (input == NULL) return EXIT_FAILURE;
    size_t len = strnlen(input, 1024);
    int upper, lower, digit, special;
    categorize_string(input, len, &upper, &lower, &digit, &special);
    printf("Input: %s\n", input);
    printf("Uppercase: %d\n", upper);
    printf("Lowercase: %d\n", lower);
    printf("Digits: %d\n", digit);
    printf("Special chars: %d\n", special);
    return EXIT_SUCCESS;
}