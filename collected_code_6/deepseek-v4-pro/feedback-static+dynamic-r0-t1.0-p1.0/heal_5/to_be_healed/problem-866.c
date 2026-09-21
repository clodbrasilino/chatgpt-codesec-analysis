#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int has_31_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    size_t len = strnlen(month, 32);
    
    /* Possible weaknesses found:
     *  Assuming that condition 'len>=32' is not redundant
     */
    if (len == 0 || len >= 32) {
        return 0;
    }
    
    /* Possible weaknesses found:
     *  Condition 'len+1>32' is always false
     *  Condition 'len+1>32' is always false [knownConditionTrueFalse]
     */
    if (len + 1 > 32) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower_month[32];
    
    size_t i;
    for (i = 0; i < len && i < sizeof(lower_month) - 1; i++) {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    lower_month[i] = '\0';
    
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
    
    for (size_t i = 0; i < sizeof(months) / sizeof(months[0]); i++) {
        if (has_31_days(months[i])) {
            printf("%s has 31 days\n", months[i]);
        } else {
            printf("%s does not have 31 days\n", months[i]);
        }
    }
    
    return 0;
}