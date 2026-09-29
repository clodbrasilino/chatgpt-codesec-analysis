#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>

long long extract_max_numeric_value(const char *str) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "-?[0-9]+";
    const char *cursor = str;
    long long max_value = 0;
    int has_value = 0;
    int reg_result;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     *  Although the value stored to 'reg_result' is used in the enclosing expression, the value is never actually read from 'reg_result' [deadcode.DeadStores]
     */
    while ((reg_result = regexec(&regex, cursor, 1, match, 0)) == 0) {
        int length = match[0].rm_eo - match[0].rm_so;
        
        /* Possible weaknesses found:
         *  Assuming that condition 'length<=0' is not redundant
         */
        if (length <= 0 || (size_t)length >= (size_t)INT_MAX) {
            cursor++;
            continue;
        }
        
        char *num_str = (char *)malloc(length + 1);
        
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (num_str == NULL) {
            regfree(&regex);
            return 0;
        }
        
        /* Possible weaknesses found:
         *  Condition 'length>0' is always true [knownConditionTrueFalse]
         *  Condition 'length>0' is always true
         */
        if (length > 0) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(num_str, cursor + match[0].rm_so, length);
        }
        num_str[length] = '\0';
        
        errno = 0;
        long long current = strtoll(num_str, NULL, 10);
        
        if (errno == ERANGE) {
            free(num_str);
            cursor += match[0].rm_eo;
            if (match[0].rm_so == match[0].rm_eo) {
                cursor++;
            }
            continue;
        }
        
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