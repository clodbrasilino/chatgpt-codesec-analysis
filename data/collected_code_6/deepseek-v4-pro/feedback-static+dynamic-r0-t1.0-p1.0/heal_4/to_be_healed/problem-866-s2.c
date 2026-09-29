#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_31_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    size_t len = strnlen(month, 32);
    
    if (len == 0 || len >= 32) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower_month[32];
    
    size_t i;
    for (i = 0; i < len && i < sizeof(lower_month) - 1; i++) {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    lower_month[i] = '\0';
    
    const char *months_31[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    
    for (size_t j = 0; j < sizeof(months_31) / sizeof(months_31[0]); j++) {
        if (strcmp(lower_month, months_31[j]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    const char *test_months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    
    for (size_t i = 0; i < sizeof(test_months) / sizeof(test_months[0]); i++) {
        if (has_31_days(test_months[i])) {
            printf("%s has 31 days.\n", test_months[i]);
        } else {
            printf("%s does not have 31 days.\n", test_months[i]);
        }
    }
    
    return 0;
}