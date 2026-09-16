#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    char lower_month[32];
    size_t len = strlen(month);
    if (len >= sizeof(lower_month)) {
        return 0;
    }
    
    for (size_t i = 0; i < len; i++) {
        lower_month[i] = tolower((unsigned char)month[i]);
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