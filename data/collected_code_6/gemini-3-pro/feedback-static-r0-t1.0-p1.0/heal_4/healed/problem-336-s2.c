#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    size_t len = strlen(month);
    char *lower_month = (char *)malloc(len + 1);
    if (lower_month == NULL) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    lower_month[len] = '\0';

    bool match = (strcmp(lower_month, "february") == 0 || strcmp(lower_month, "feb") == 0);
    
    free(lower_month);
    return match;
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