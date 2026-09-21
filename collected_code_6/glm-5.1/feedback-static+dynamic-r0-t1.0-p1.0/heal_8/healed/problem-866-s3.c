#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_31_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    size_t len = strnlen(month, 15);
    if (len >= 15) {
        return 0;
    }

    char lower[16];
    for (size_t i = 0; i < len; i++) {
        lower[i] = (char)tolower((unsigned char)month[i]);
    }
    lower[len] = '\0';

    const char *months_with_31[] = {"january", "march", "may", "july", "august", "october", "december"};
    size_t num_months = sizeof(months_with_31) / sizeof(months_with_31[0]);
    for (size_t i = 0; i < num_months; i++) {
        if (strncmp(lower, months_with_31[i], 16) == 0) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    const char *test_months[] = {
        "January", "february", "MARCh", "April", "MAY", "June",
        "JuLy", "August", "September", "october", "November", "december", NULL
    };

    for (size_t i = 0; test_months[i] != NULL; i++) {
        int result = has_31_days(test_months[i]);
        printf("%s: %d\n", test_months[i], result);
    }

    return 0;
}