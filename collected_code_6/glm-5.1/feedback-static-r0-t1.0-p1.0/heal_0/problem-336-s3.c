#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    char lower[10];
    size_t len = strlen(month);
    if (len == 0 || len >= sizeof(lower)) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        lower[i] = (char)tolower((unsigned char)month[i]);
    }
    lower[len] = '\0';

    const char *months[] = {
        "january", "february", "march", "april", "may", "june",
        "july", "august", "september", "october", "november", "december"
    };

    int found = 0;
    for (size_t i = 0; i < sizeof(months) / sizeof(months[0]); i++) {
        if (strcmp(lower, months[i]) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        return 0;
    }

    return 1;
}

int main(void) {
    const char *test_months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December",
        "Invalid", "", NULL
    };

    for (size_t i = 0; i < sizeof(test_months) / sizeof(test_months[0]); i++) {
        if (test_months[i] != NULL) {
            if (has_28_days(test_months[i])) {
                printf("%s contains 28 days\n", test_months[i]);
            } else {
                printf("%s does not contain 28 days or is invalid\n", test_months[i]);
            }
        }
    }

    return 0;
}