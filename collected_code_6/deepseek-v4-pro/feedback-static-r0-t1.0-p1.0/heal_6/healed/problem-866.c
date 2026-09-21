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
    
    char lower_month[32];
    size_t copy_len = len < 31 ? len : 31;
    
    for (size_t i = 0; i < copy_len; i++) {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    lower_month[copy_len] = '\0';
    
    return (strcmp(lower_month, "january") == 0 ||
            strcmp(lower_month, "march") == 0 ||
            strcmp(lower_month, "may") == 0 ||
            strcmp(lower_month, "july") == 0 ||
            strcmp(lower_month, "august") == 0 ||
            strcmp(lower_month, "october") == 0 ||
            strcmp(lower_month, "december") == 0);
}

int main(void) {
    const char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    
    for (size_t i = 0; i < 12; i++) {
        if (has_31_days(months[i])) {
            printf("%s has 31 days\n", months[i]);
        } else {
            printf("%s does not have 31 days\n", months[i]);
        }
    }
    
    return 0;
}