#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int count_matches(const char *str, const char *pattern) {
    if (str == NULL || pattern == NULL) {
        return 0;
    }

    regex_t regex;
    int count = 0;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 0;
    }

    regmatch_t pmatch[1];
    const char *cursor = str;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        count++;
        cursor += pmatch[0].rm_eo;
        if (pmatch[0].rm_so == pmatch[0].rm_eo) {
            cursor++;
        }
        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);
    return count;
}

void analyze_string(const char *str, int *upper, int *lower, int *numeric, int *special) {
    if (str == NULL || upper == NULL || lower == NULL || numeric == NULL || special == NULL) {
        return;
    }

    *upper = count_matches(str, "[A-Z]");
    *lower = count_matches(str, "[a-z]");
    *numeric = count_matches(str, "[0-9]");
    *special = count_matches(str, "[^a-zA-Z0-9 \t\n\r\v\f]");
}

int main(void) {
    const char *test_str = "SecurePa$$w0rd! 2023";
    int upper = 0;
    int lower = 0;
    int numeric = 0;
    int special = 0;

    analyze_string(test_str, &upper, &lower, &numeric, &special);

    printf("String: %s\n", test_str);
    printf("Uppercase: %d\n", upper);
    printf("Lowercase: %d\n", lower);
    printf("Numeric: %d\n", numeric);
    printf("Special: %d\n", special);

    return 0;
}