#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_30_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower[32];
    size_t len = 0;
    
    while (len < sizeof(lower) - 1 && month[len] != '\0') {
        lower[len] = tolower((unsigned char)month[len]);
        len++;
    }
    
    if (month[len] != '\0' && len == sizeof(lower) - 1) {
        return 0;
    }
    
    lower[len] = '\0';
    
    const char *months_30[] = {
        "april", "june", "september", "november"
    };
    
    for (size_t i = 0; i < sizeof(months_30) / sizeof(months_30[0]); i++) {
        if (strcmp(lower, months_30[i]) == 0) {
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
     *  Assignment 'null_month=NULL', assigned value is 0
     */
    const char *null_month = NULL;
    /* Possible weaknesses found:
     *  Condition 'null_month!=NULL' is always false
     *  Condition 'null_month!=NULL' is always false [knownConditionTrueFalse]
     */
    if (null_month != NULL && has_30_days(null_month)) {
        printf("NULL: has 30 days\n");
    } else {
        printf("NULL: does not have 30 days\n");
    }
    
    return 0;
}