#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_30_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    char lower_month[32];
    size_t len = strlen(month);
    if (len == 0 || len >= sizeof(lower_month)) {
        return 0;
    }
    
    for (size_t i = 0; i < len; i++) {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    lower_month[len] = '\0';
    
    const char *months_30[] = {
        "april", "june", "september", "november"
    };
    
    for (size_t i = 0; i < sizeof(months_30) / sizeof(months_30[0]); i++) {
        if (strcmp(lower_month, months_30[i]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    const char *test_months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December",
        "april", "JUNE", "September", "NOVEMBER", "", NULL
    };
    
    for (size_t i = 0; test_months[i] != NULL; i++) {
        printf("%s: %s\n", test_months[i], 
               has_30_days(test_months[i]) ? "has 30 days" : "does not have 30 days");
    }
    
    printf("NULL: %s\n", has_30_days(NULL) ? "has 30 days" : "does not have 30 days");
    
    return 0;
}