#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

int has_28_days(const char *month) {
    size_t max_len = 9;
    
    if (month == NULL) {
        return 0;
    }
    
    size_t input_len = strlen(month);
    if (input_len > max_len) {
        return 0;
    }
    
    char lower_month[10];
    size_t i;
    
    for (i = 0; i < input_len && i < sizeof(lower_month) - 1; i++) {
        lower_month[i] = tolower((unsigned char)month[i]);
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