#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower_month[32];
    size_t len = 0;
    size_t max_len = sizeof(lower_month) - 1;
    
    while (len < max_len && month[len] != '\0') {
        lower_month[len] = tolower((unsigned char)month[len]);
        len++;
    }
    
    if (len >= max_len || month[len] != '\0') {
        return 0;
    }
    
    lower_month[len] = '\0';
    
    return strcmp(lower_month, "february") == 0;
}

int main(void) {
    const char *test_months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December",
        "february", "FEBRUARY", "Feb", NULL
    };
    
    for (int i = 0; test_months[i] != NULL; i++) {
        printf("%s: %s\n", test_months[i], 
               has_28_days(test_months[i]) ? "28 days" : "not 28 days");
    }
    
    printf("NULL: not 28 days\n");
    
    return 0;
}