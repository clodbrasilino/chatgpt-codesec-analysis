#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    size_t len = strnlen(month, 16);
    if (len == 0 || len >= 16) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower[17];
    for (size_t i = 0; i < len; i++) {
        lower[i] = (char)tolower((unsigned char)month[i]);
    }
    lower[len] = '\0';

    return strcmp(lower, "february") == 0;
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