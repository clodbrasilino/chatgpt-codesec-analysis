#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    char lower_month[16];
    size_t i;
    
    for (i = 0; i < sizeof(lower_month) - 1 && month[i] != '\0'; i++) {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    lower_month[i] = '\0';

    if (month[i] != '\0') {
        return false;
    }

    if (strcmp(lower_month, "february") == 0 || strcmp(lower_month, "feb") == 0) {
        return true;
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