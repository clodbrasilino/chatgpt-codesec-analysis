#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int has_30_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    const char *months_30[] = {
        "april", "june", "september", "november"
    };
    
    size_t num_months = sizeof(months_30) / sizeof(months_30[0]);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t month_len = strlen(month);
    
    if (month_len == 0 || month_len > 255) {
        return 0;
    }
    
    for (size_t m = 0; m < num_months; m++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t target_len = strlen(months_30[m]);
        if (month_len != target_len) {
            continue;
        }
        
        int match = 1;
        for (size_t i = 0; i < month_len; i++) {
            if (tolower((unsigned char)month[i]) != (unsigned char)months_30[m][i]) {
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
        "January", "february", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December",
        "april", "JUNE", "SePtEmBeR", NULL
    };
    
    for (size_t i = 0; test_months[i] != NULL; i++) {
        printf("%s: %s\n", test_months[i], 
               has_30_days(test_months[i]) ? "has 30 days" : "does not have 30 days");
    }
    
    /* Possible weaknesses found:
     *  Calling function 'has_30_days' returns 0
     *  Condition 'has_30_days(NULL)' is always false
     *  Condition 'has_30_days(NULL)' is always false [knownConditionTrueFalse]
     */
    if (has_30_days(NULL)) {
        printf("NULL: has 30 days\n");
    } else {
        printf("NULL: does not have 30 days\n");
    }
    
    return 0;
}