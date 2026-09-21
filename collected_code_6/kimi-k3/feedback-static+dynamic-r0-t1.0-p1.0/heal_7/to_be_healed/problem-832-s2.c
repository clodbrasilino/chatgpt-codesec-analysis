#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>
#include <errno.h>

int extract_max_numeric(const char *str, size_t str_len, double *max_value) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[0-9]+(\\.[0-9]+)?";
    int ret;
    int found = 0;
    double current_max = 0.0;
    
    if (str == NULL || max_value == NULL) {
        return -1;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }
    
    const char *cursor = str;
    size_t remaining_len = str_len;
    
    while (remaining_len > 0) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret != 0) {
            break;
        }
        
        int start = match.rm_so;
        int end = match.rm_eo;
        
        if (start < 0 || end < 0 || end <= start) {
            break;
        }
        
        size_t len = (size_t)(end - start);
        
        /* Possible weaknesses found:
         *  Assuming that condition 'len>remaining_len-(unsigned long)start' is not redundant
         */
        if ((size_t)end > remaining_len || (size_t)start >= remaining_len || len > remaining_len - (size_t)start) {
            break;
        }
        
        char *num_str = (char *)malloc(len + 1);
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (num_str == NULL) {
            regfree(&regex);
            return -1;
        }
        
        /* Possible weaknesses found:
         *  Condition 'len<=remaining_len-(unsigned long)start' is always true [knownConditionTrueFalse]
         *  Condition 'len<=remaining_len-(unsigned long)start' is always true
         */
        if (len > 0 && len <= remaining_len - (size_t)start) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(num_str, cursor + start, len);
            num_str[len] = '\0';
        } else {
            free(num_str);
            break;
        }
        
        char *endptr;
        errno = 0;
        double value = strtod(num_str, &endptr);
        
        if (endptr != num_str && errno != ERANGE) {
            if (!found || value > current_max) {
                current_max = value;
                found = 1;
            }
        }
        
        free(num_str);
        cursor += end;
        remaining_len -= (size_t)end;
    }
    
    regfree(&regex);
    
    if (found) {
        *max_value = current_max;
        return 0;
    }
    
    return 1;
}

int main(void) {
    const char *test_strings[] = {
        "The values are 42, 3.14, and 100",
        "No numbers here",
        "Max is 999.99 and min is 0.001",
        "12345",
        ""
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        double max_val;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t str_len = strlen(test_strings[i]);
        int result = extract_max_numeric(test_strings[i], str_len, &max_val);
        
        if (result == 0) {
            printf("String: \"%s\" -> Max: %f\n", test_strings[i], max_val);
        } else if (result == 1) {
            printf("String: \"%s\" -> No numeric value found\n", test_strings[i]);
        } else {
            printf("String: \"%s\" -> Error occurred\n", test_strings[i]);
        }
    }
    
    return 0;
}