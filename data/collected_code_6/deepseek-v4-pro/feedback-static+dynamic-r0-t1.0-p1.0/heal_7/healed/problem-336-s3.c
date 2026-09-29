#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int has_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    size_t len = strnlen(month, 32);
    
    if (len == 0 || len >= 32) {
        return 0;
    }
    
    char lower_month[32];
    size_t i;
    
    for (i = 0; i < len && i < sizeof(lower_month) - 1; i++) {
        lower_month[i] = (char)tolower((unsigned char)month[i]);
    }
    lower_month[i] = '\0';
    
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