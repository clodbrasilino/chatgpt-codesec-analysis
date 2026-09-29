#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int has_30_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    size_t len = strnlen(month, 32);
    
    if (len == 0 || len >= 32) {
        return 0;
    }
    
    if (month[len] != '\0') {
        return 0;
    }
    
    const char *months_30[] = {
        "april", "june", "september", "november"
    };
    
    size_t num_months = sizeof(months_30) / sizeof(months_30[0]);
    
    for (size_t j = 0; j < num_months; j++) {
        const char *expected = months_30[j];
        size_t expected_len = strlen(expected);
        
        if (len != expected_len) {
            continue;
        }
        
        int match = 1;
        for (size_t i = 0; i < len; i++) {
            if (tolower((unsigned char)month[i]) != expected[i]) {
                match = 0;
                break;
            }
        }
        
        if (match) {
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
    
    return 0;
}