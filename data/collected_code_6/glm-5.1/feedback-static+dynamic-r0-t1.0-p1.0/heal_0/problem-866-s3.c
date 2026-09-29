#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_31_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    char lower[16] = {0};
    size_t len = strlen(month);
    if (len >= sizeof(lower)) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        lower[i] = (char)tolower((unsigned char)month[i]);
    }
    lower[len] = '\0';

    if (strcmp(lower, "january") == 0) return 1;
    if (strcmp(lower, "march") == 0) return 1;
    if (strcmp(lower, "may") == 0) return 1;
    if (strcmp(lower, "july") == 0) return 1;
    if (strcmp(lower, "august") == 0) return 1;
    if (strcmp(lower, "october") == 0) return 1;
    if (strcmp(lower, "december") == 0) return 1;

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