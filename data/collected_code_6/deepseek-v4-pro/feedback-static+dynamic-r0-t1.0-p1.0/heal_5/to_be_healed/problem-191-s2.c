#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int has_30_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower[16];
    size_t len = 0;
    size_t max_len = sizeof(lower) - 1;
    
    while (len < max_len && month[len] != '\0') {
        lower[len] = tolower((unsigned char)month[len]);
        len++;
    }
    
    if (month[len] != '\0') {
        return 0;
    }
    
    lower[len] = '\0';
    
    const char *months_30[] = {
        "april", "june", "september", "november"
    };
    
    size_t num_months = sizeof(months_30) / sizeof(months_30[0]);
    for (size_t i = 0; i < num_months; i++) {
        if (strncmp(lower, months_30[i], sizeof(lower)) == 0) {
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
    
    const char *null_month = NULL;
    /* Possible weaknesses found:
     *  Condition 'has_30_days(null_month)' is always false
     *  Calling function 'has_30_days' returns 0
     *  Condition 'has_30_days(null_month)' is always false [knownConditionTrueFalse]
     */
    printf("NULL: %s\n", has_30_days(null_month) ? "has 30 days" : "does not have 30 days");
    
    return 0;
}