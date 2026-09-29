#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

long long extract_max_numeric_value(const char *str) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "-?[0-9]+";
    const char *cursor = str;
    long long max_value = 0;
    int has_value = 0;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 0;
    }
    
    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        int length = match[0].rm_eo - match[0].rm_so;
        char *num_str = (char *)malloc(length + 1);
        
        if (num_str == NULL) {
            regfree(&regex);
            return 0;
        }
        
        strncpy(num_str, cursor + match[0].rm_so, length);
        num_str[length] = '\0';
        
        long long current = atoll(num_str);
        free(num_str);
        
        if (!has_value || current > max_value) {
            max_value = current;
            has_value = 1;
        }
        
        cursor += match[0].rm_eo;
        
        if (match[0].rm_so == match[0].rm_eo) {
            cursor++;
        }
    }
    
    regfree(&regex);
    return max_value;
}

int main(void) {
    const char *test_strings[] = {
        "abc123def456",
        "negative-42 and 100",
        "no numbers here",
        "-500 -100 -50",
        "mixed-10text20-30",
        "12345678901234567890",
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        long long result = extract_max_numeric_value(test_strings[i]);
        printf("String: %s\n", test_strings[i]);
        printf("Max numeric value: %lld\n\n", result);
    }
    
    return 0;
}