#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_30_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    size_t len = strnlen(month, 31);
    if (len == 0 || len >= 31) {
        return 0;
    }
    
    char lower[32];
    size_t i;
    for (i = 0; i < len; i++) {
        lower[i] = (char)tolower((unsigned char)month[i]);
    }
    lower[i] = '\0';
    
    const char *months_30[] = {
        "april", "june", "september", "november"
    };
    int num_months = sizeof(months_30) / sizeof(months_30[0]);
    
    for (int j = 0; j < num_months; j++) {
        if (strcmp(lower, months_30[j]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    const char *test_months[] = {
        "January", "february", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December",
        "april", "JUNE", "SePtEmBeR", NULL
    };
    
    for (int i = 0; test_months[i] != NULL; i++) {
        printf("%s: %s\n", test_months[i], 
               has_30_days(test_months[i]) ? "has 30 days" : "does not have 30 days");
    }
    
    printf("NULL: %s\n", "does not have 30 days");
    
    return 0;
}