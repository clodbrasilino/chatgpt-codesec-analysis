#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_case_insensitive_equal(const char *str1, const char *str2);
bool has_31_days(const char *month);

bool is_case_insensitive_equal(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    while (*str1 && *str2) {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) {
            return false;
        }
        str1++;
        str2++;
    }
    return *str1 == '\0' && *str2 == '\0';
}

bool has_31_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    if (is_case_insensitive_equal(month, "january") ||
        is_case_insensitive_equal(month, "march") ||
        is_case_insensitive_equal(month, "may") ||
        is_case_insensitive_equal(month, "july") ||
        is_case_insensitive_equal(month, "august") ||
        is_case_insensitive_equal(month, "october") ||
        is_case_insensitive_equal(month, "december")) {
        return true;
    }
    
    return false;
}

int main(void) {
    size_t input_size = 64;
    char *input = (char *)malloc(input_size);
    
    if (input == NULL) {
        return 1;
    }
    
    if (fgets(input, (int)input_size, stdin) != NULL) {
        char *newline = strchr(input, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        
        if (has_31_days(input)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    } else {
        free(input);
        return 1;
    }
    
    free(input);
    return 0;
}