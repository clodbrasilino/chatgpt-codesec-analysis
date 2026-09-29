#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int has_31_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    size_t len = strnlen(month, 31);
    
    if (len == 0 || len >= 31) {
        return 0;
    }
    
    char *lower_month = malloc(len + 1);
    if (lower_month == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < len; i++) {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    lower_month[len] = '\0';
    
    const char *months_31[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    
    int result = 0;
    for (size_t j = 0; j < sizeof(months_31) / sizeof(months_31[0]); j++) {
        if (strcmp(lower_month, months_31[j]) == 0) {
            result = 1;
            break;
        }
    }
    
    free(lower_month);
    return result;
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