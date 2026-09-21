#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_case_insensitive_equal(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) {
            return false;
        }
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    if (is_case_insensitive_equal(month, "february")) {
        return true;
    }
    
    const char *other_months[] = {
        "january", "march", "april", "may", "june",
        "july", "august", "september", "october",
        "november", "december"
    };
    
    for (int i = 0; i < 11; i++) {
        if (is_case_insensitive_equal(month, other_months[i])) {
            return false;
        }
    }
    
    return false;
}

int main(void) {
    size_t buffer_size = 128;
    char *month = (char *)malloc(buffer_size);
    if (month == NULL) {
        return 1;
    }

    if (fgets(month, (int)buffer_size, stdin) != NULL) {
        size_t newline_idx = strcspn(month, "\r\n");
        month[newline_idx] = '\0';
        
        if (has_28_days(month)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    free(month);
    return 0;
}