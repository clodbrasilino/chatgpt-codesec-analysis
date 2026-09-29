#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void categorize_string(const char *str, int *upper, int *lower, int *digit, int *special) {
    *upper = 0;
    *lower = 0;
    *digit = 0;
    *special = 0;
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        const char c = str[i];
        if (isupper((unsigned char)c)) {
            (*upper)++;
        } else if (islower((unsigned char)c)) {
            (*lower)++;
        } else if (isdigit((unsigned char)c)) {
            (*digit)++;
        } else {
            (*special)++;
        }
    }
}

int main(void) {
    const char *input = "Hello World! 123 @#$";
    int upper, lower, digit, special;
    categorize_string(input, &upper, &lower, &digit, &special);
    printf("Input: %s\n", input);
    printf("Uppercase: %d\n", upper);
    printf("Lowercase: %d\n", lower);
    printf("Digits: %d\n", digit);
    printf("Special chars: %d\n", special);
    return 0;
}