#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

static int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int has_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    const char *february = "february";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t feb_len = strlen(february);
    size_t month_len = 0;
    
    while (month[month_len] != '\0') {
        if (month_len >= feb_len) {
            break;
        }
        month_len++;
    }
    
    if (month[month_len] != '\0' || month_len != feb_len) {
        return 0;
    }
    
    for (size_t i = 0; i < month_len; i++) {
        if (tolower((unsigned char)month[i]) != february[i]) {
            return 0;
        }
    }
    
    return 1;
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