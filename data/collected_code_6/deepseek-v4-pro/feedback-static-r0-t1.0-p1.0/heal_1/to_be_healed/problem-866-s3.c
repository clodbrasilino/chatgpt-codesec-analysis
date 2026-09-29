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
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(month);
    
    if (len >= sizeof(lower_month)) {
        return 0;
    }
    
    for (size_t i = 0; i < len; i++) {
        lower_month[i] = tolower((unsigned char)month[i]);
    }
    lower_month[len] = '\0';
    
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
        "September", "October", "November", "December",
        "JANUARY", "march", "InvalidMonth", NULL
    };
    
    for (int i = 0; test_months[i] != NULL; i++) {
        printf("%s: %s\n", test_months[i], 
               has_31_days(test_months[i]) ? "31 days" : "not 31 days");
    }
    
    return 0;
}