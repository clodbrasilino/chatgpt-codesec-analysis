#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

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

void categorize_string(const char *str, int *upper, int *lower, int *digit, int *special) {
    *upper = 0;
    *lower = 0;
    *digit = 0;
    *special = 0;
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        /* Possible weaknesses found:
         *  Variable 'c' can be declared as const array [constVariable]
         */
        char c[2] = {str[i], '\0'};
        if (match_regex("[A-Z]", c)) {
            (*upper)++;
        } else if (match_regex("[a-z]", c)) {
            (*lower)++;
        } else if (match_regex("[0-9]", c)) {
            (*digit)++;
        } else if (match_regex("[^A-Za-z0-9]", c)) {
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