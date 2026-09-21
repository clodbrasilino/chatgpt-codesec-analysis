#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int match_regex(const char *pattern, const char *string) {
    regex_t regex;
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }
    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);
    if (ret == 0) {
        return 1;
    }
    return 0;
}

void categorize_string(const char *str, size_t len, int *upper, int *lower, int *digit, int *special) {
    *upper = 0;
    *lower = 0;
    *digit = 0;
    *special = 0;
    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        if (isupper((unsigned char)c)) {
            (*upper)++;
        } else if (islower((unsigned char)c)) {
            (*lower)++;
        } else if (isdigit((unsigned char)c)) {
            (*digit)++;
        } else if (!isalnum((unsigned char)c) && isprint((unsigned char)c)) {
            (*special)++;
        }
    }
}

int main(void) {
    const char *input = "Hello World! 123 @#$";
    size_t len = strlen(input);
    int upper, lower, digit, special;
    categorize_string(input, len, &upper, &lower, &digit, &special);
    printf("Input: %s\n", input);
    printf("Uppercase: %d\n", upper);
    printf("Lowercase: %d\n", lower);
    printf("Digits: %d\n", digit);
    printf("Special chars: %d\n", special);
    return 0;
}