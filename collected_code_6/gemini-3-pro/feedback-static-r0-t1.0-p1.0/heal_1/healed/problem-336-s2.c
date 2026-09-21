#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    char lower_month[20];
    size_t i = 0;

    while (i < sizeof(lower_month) - 1 && month[i] != '\0') {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
        i++;
    }
    lower_month[i] = '\0';

    if (strcmp(lower_month, "february") == 0 || strcmp(lower_month, "feb") == 0) {
        return true;
    }
    
    const char *other_months[] = {
        "january", "jan", "march", "mar", "april", "apr", "may", "june", "jun",
        "july", "jul", "august", "aug", "september", "sep", "october", "oct",
        "november", "nov", "december", "dec"
    };

    for (size_t j = 0; j < sizeof(other_months) / sizeof(other_months[0]); j++) {
        if (strcmp(lower_month, other_months[j]) == 0) {
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