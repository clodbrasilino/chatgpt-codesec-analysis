#include <stdio.h>
#include <string.h>
#include <ctype.h>

int strequal_nocase(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == *b;
}

int has_30_days(const char *month_name) {
    if (month_name == NULL) {
        return 0;
    }

    if (strequal_nocase(month_name, "april") || 
        strequal_nocase(month_name, "june") || 
        strequal_nocase(month_name, "september") || 
        strequal_nocase(month_name, "november") ||
        strequal_nocase(month_name, "apr") ||
        strequal_nocase(month_name, "jun") ||
        strequal_nocase(month_name, "sep") ||
        strequal_nocase(month_name, "nov")) {
        return 1;
    }

    return 0;
}

int main(void) {
    const char *test_months[] = {
        "April", "January", "june", "FEBRUARY", "September", "nov", NULL
    };

    for (size_t i = 0; test_months[i] != NULL; i++) {
        if (has_30_days(test_months[i])) {
            printf("%s has 30 days.\n", test_months[i]);
        } else {
            printf("%s does not have 30 days.\n", test_months[i]);
        }
    }

    return 0;
}