#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower[10];
    size_t len = strnlen(month, sizeof(lower));
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

    for (size_t i = 0; i < sizeof(months) / sizeof(months[0]); i++) {
        if (strncmp(lower, months[i], sizeof(lower)) == 0) {
            return 1;
        }
    }

    return 0;
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