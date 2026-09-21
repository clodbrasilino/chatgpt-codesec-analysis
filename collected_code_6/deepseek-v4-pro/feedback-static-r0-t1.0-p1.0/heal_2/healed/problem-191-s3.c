#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_30_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    size_t len = 0;
    while (len < 31 && month[len] != '\0') {
        len++;
    }
    
    if (len == 0 || month[len] != '\0') {
        return 0;
    }
    
    char lower_month[32];
    size_t i;
    for (i = 0; i < len && i < 31; i++) {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    lower_month[i] = '\0';
    
    const char *months_30[] = {
        "april", "june", "september", "november"
    };
    
    for (size_t j = 0; j < sizeof(months_30) / sizeof(months_30[0]); j++) {
        if (strcmp(lower_month, months_30[j]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    const char *test_months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December",
        "april", "JUNE", "September", "NOVEMBER", ""
    };
    
    size_t num_months = sizeof(test_months) / sizeof(test_months[0]);
    
    for (size_t i = 0; i < num_months; i++) {
        printf("%s: %s\n", test_months[i], 
               has_30_days(test_months[i]) ? "has 30 days" : "does not have 30 days");
    }
    
    printf("NULL: %s\n", has_30_days(NULL) ? "has 30 days" : "does not have 30 days");
    
    return 0;
}