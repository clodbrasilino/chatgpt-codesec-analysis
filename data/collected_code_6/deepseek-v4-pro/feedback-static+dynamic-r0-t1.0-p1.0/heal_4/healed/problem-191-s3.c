#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int has_30_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    size_t len = strlen(month);
    if (len == 0 || len > 31) {
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
    
    const char *months_30[] = {
        "april", "june", "september", "november"
    };
    
    size_t num_months = sizeof(months_30) / sizeof(months_30[0]);
    int result = 0;
    for (size_t i = 0; i < num_months; i++) {
        if (strcmp(lower_month, months_30[i]) == 0) {
            result = 1;
            break;
        }
    }
    
    free(lower_month);
    return result;
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
    
    return 0;
}