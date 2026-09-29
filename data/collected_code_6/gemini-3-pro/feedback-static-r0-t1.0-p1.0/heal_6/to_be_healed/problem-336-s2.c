#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower_month[9];
    size_t i;
    for (i = 0; i < 8; i++) {
        if (month[i] == '\0') {
            break;
        }
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    
    if (month[i] != '\0') {
        return false;
    }
    
    lower_month[i] = '\0';

    return (strcmp(lower_month, "february") == 0 || strcmp(lower_month, "feb") == 0);
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