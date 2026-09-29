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
    
    while (len < sizeof(lower_month) - 1 && month[len] != '\0') {
        lower_month[len] = tolower((unsigned char)month[len]);
        len++;
    }
    
    if (month[len] != '\0') {
        return 0;
    }
    
    lower_month[len] = '\0';
    
    return strcmp(lower_month, "february") == 0;
}

int main(void) {
    const char *months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };
    
    for (int i = 0; i < 12; i++) {
        printf("%s has %s\n", months[i], 
               has_28_days(months[i]) ? "28 days" : "not 28 days");
    }
    
    return 0;
}