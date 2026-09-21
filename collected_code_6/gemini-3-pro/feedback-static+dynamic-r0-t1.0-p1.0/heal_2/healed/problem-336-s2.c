#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static bool is_case_insensitive_match(const char *str, const char *expected_lower) {
    while (*str != '\0' && *expected_lower != '\0') {
        if (tolower((unsigned char)*str) != *expected_lower) {
            return false;
        }
        str++;
        expected_lower++;
    }
    return *str == '\0' && *expected_lower == '\0';
}

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    if (is_case_insensitive_match(month, "february") || is_case_insensitive_match(month, "feb")) {
        return true;
    }
    
    const char *other_months[] = {
        "january", "jan", "march", "mar", "april", "apr", "may", "june", "jun",
        "july", "jul", "august", "aug", "september", "sep", "october", "oct",
        "november", "nov", "december", "dec"
    };

    for (size_t j = 0; j < sizeof(other_months) / sizeof(other_months[0]); j++) {
        if (is_case_insensitive_match(month, other_months[j])) {
            return false;
        }
    }

    return false;
}

int main(void) {
    const char *test_months[] = {"February", "feb", "JANUARY", "April", "Invalid", NULL};
    
    for (size_t i = 0; i < sizeof(test_months) / sizeof(test_months[0]); i++) {
        if (test_months[i] != NULL) {
            bool result = has_28_days(test_months[i]);
            printf("%s: %s\n", test_months[i], result ? "Yes" : "No");
        } else {
            bool result = has_28_days(test_months[i]);
            printf("NULL: %s\n", result ? "Yes" : "No");
        }
    }
    
    return 0;
}