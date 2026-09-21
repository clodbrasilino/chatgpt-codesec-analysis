#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>

long extract_max_numeric_value(const char *str) {
    if (!str) {
        return LONG_MIN;
    }

    regex_t regex;
    int reti;
    long max_val = LONG_MIN;
    int found = 0;

    reti = regcomp(&regex, "-?[0-9]+", REG_EXTENDED);
    if (reti) {
        return LONG_MIN;
    }

    regmatch_t matches[1];
    const char *p = str;

    while (regexec(&regex, p, 1, matches, 0) == 0) {
        size_t len = matches[0].rm_eo - matches[0].rm_so;
        char *num_str = (char *)malloc(len + 1);
        
        if (num_str) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(num_str, p + matches[0].rm_so, len);
            num_str[len] = '\0';
            
            char *endptr;
            long val = strtol(num_str, &endptr, 10);
            
            if (*endptr == '\0') {
                if (!found || val > max_val) {
                    max_val = val;
                    found = 1;
                }
            }
            free(num_str);
        }
        
        p += matches[0].rm_eo;
    }

    regfree(&regex);

    return found ? max_val : LONG_MIN;
}

int main() {
    const char *test_str = "The temperatures were -5, 42, 108, and 3 degrees.";
    long max_val = extract_max_numeric_value(test_str);
    
    if (max_val != LONG_MIN) {
        printf("Max value: %ld\n", max_val);
    } else {
        printf("No numeric value found or error occurred.\n");
    }

    return 0;
}