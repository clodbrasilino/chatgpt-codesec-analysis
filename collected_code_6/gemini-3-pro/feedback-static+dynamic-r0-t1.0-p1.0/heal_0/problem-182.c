#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int check_regex(const char *pattern, const char *str) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    }

    return -1;
}

void analyze_string(const char *str) {
    int has_upper;
    int has_lower;
    int has_digit;
    int has_special;

    if (str == NULL) {
        fprintf(stderr, "Input string is NULL\n");
        return;
    }

    has_upper = check_regex("[A-Z]", str);
    has_lower = check_regex("[a-z]", str);
    has_digit = check_regex("[0-9]", str);
    has_special = check_regex("[^a-zA-Z0-9 \t\n\r\v\f]", str);

    if (has_upper == -1 || has_lower == -1 || has_digit == -1 || has_special == -1) {
        fprintf(stderr, "Error compiling or executing regex\n");
        return;
    }

    printf("String: '%s'\n", str);
    printf("Contains Uppercase: %s\n", has_upper ? "Yes" : "No");
    printf("Contains Lowercase: %s\n", has_lower ? "Yes" : "No");
    printf("Contains Numeric: %s\n", has_digit ? "Yes" : "No");
    printf("Contains Special Character: %s\n", has_special ? "Yes" : "No");
}

int main(void) {
    const char *test_string_1 = "HelloWorld123!";
    const char *test_string_2 = "alllowercase";

    analyze_string(test_string_1);
    printf("\n");
    analyze_string(test_string_2);

    return EXIT_SUCCESS;
}