#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t month_len = strlen(month);
    
    char *lower_month = (char *)malloc(month_len + 1);
    if (lower_month == NULL) {
        return false;
    }

    for (size_t i = 0; i < month_len; i++) {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    lower_month[month_len] = '\0';

    bool result = false;
    if (strcmp(lower_month, "february") == 0 || strcmp(lower_month, "feb") == 0) {
        result = true;
    }
    
    free(lower_month);
    return result;
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