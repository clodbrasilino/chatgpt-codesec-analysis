#include <stdio.h>
#include <ctype.h>

int case_insensitive_match(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    while (*str1 && *str2) {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) {
            return 0;
        }
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

int has_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    if (case_insensitive_match(month, "february") || case_insensitive_match(month, "feb")) {
        return 1;
    }

    return 0;
}

int main(void) {
    const char *test_months[] = {"February", "March", "Feb", "january", NULL};
    
    for (int i = 0; i < 5; i++) {
        if (test_months[i] != NULL) {
            if (has_28_days(test_months[i])) {
                printf("%s has 28 days.\n", test_months[i]);
            } else {
                printf("%s does not have 28 days.\n", test_months[i]);
            }
        }
    }

    return 0;
}