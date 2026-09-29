#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    char lower_month[9];
    size_t i;
    
    for (i = 0; i < sizeof(lower_month) - 1; i++) {
        if (month[i] == '\0') {
            break;
        }
        lower_month[i] = tolower((unsigned char)month[i]);
    }
    
    if (i >= sizeof(lower_month) - 1 && month[i] != '\0') {
        return 0;
    }
    
    lower_month[i] = '\0';
    
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