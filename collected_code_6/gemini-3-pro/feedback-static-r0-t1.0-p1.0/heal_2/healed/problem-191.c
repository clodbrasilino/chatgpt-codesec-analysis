#include <stdio.h>
#include <string.h>
#include <ctype.h>

int streq_nocase(const char *a, const char *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == *b;
}

int has_30_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    if (streq_nocase(month, "april") ||
        streq_nocase(month, "june") ||
        streq_nocase(month, "september") ||
        streq_nocase(month, "november")) {
        return 1;
    }

    return 0;
}

int main(void) {
    const char *test_months[] = {"April", "February", "September", "january", "JUNE", NULL};
    
    for (int i = 0; test_months[i] != NULL; i++) {
        if (has_30_days(test_months[i])) {
            printf("%s has 30 days.\n", test_months[i]);
        } else {
            printf("%s does not have exactly 30 days.\n", test_months[i]);
        }
    }

    return 0;
}