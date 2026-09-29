#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(month);
    if (len == 0 || len >= 16) {
        return false;
    }

    return strcasecmp(month, "february") == 0;
}

int main(void) {
    const char *test_months[] = {"January", "February", "february", "FEBRUARY", "March", NULL};
    
    for (size_t i = 0; test_months[i] != NULL; i++) {
        if (has_28_days(test_months[i])) {
            printf("%s contains 28 days\n", test_months[i]);
        } else {
            printf("%s does not contain 28 days exclusively (or is invalid)\n", test_months[i]);
        }
    }

    return 0;
}