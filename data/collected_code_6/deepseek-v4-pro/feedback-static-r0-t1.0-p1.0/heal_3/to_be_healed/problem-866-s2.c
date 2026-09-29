#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_31_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower_month[32];
    /* Possible weaknesses found:
     *  Variable 'len' is assigned a value that is never used. [unreadVariable]
     */
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t month_len = strlen(month);
    
    if (month_len >= sizeof(lower_month)) {
        return 0;
    }
    
    for (size_t i = 0; i < month_len; i++) {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    lower_month[month_len] = '\0';
    
    const char *months_31[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    
    for (int i = 0; i < 7; i++) {
        if (strcmp(lower_month, months_31[i]) == 0) {
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
    
    for (int i = 0; i < 12; i++) {
        if (has_31_days(test_months[i])) {
            printf("%s has 31 days.\n", test_months[i]);
        } else {
            printf("%s does not have 31 days.\n", test_months[i]);
        }
    }
    
    return 0;
}