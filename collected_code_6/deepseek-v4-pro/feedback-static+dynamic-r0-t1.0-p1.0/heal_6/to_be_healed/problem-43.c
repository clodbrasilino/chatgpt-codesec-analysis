#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_lowercase_underscore_sequences(const char *input, char ***matches, size_t *match_count) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "[a-z]+_[a-z]+";
    int ret;
    size_t capacity = 10;
    size_t count = 0;
    const char *p = input;
    
    *matches = NULL;
    *match_count = 0;
    
    if (!input) {
        return -1;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return -1;
    }
    
    *matches = malloc(capacity * sizeof(char *));
    if (!*matches) {
        regfree(&regex);
        return -1;
    }
    
    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        size_t len = pmatch[0].rm_eo - pmatch[0].rm_so;
        
        if (count >= capacity) {
            size_t new_capacity = capacity * 2;
            char **new_matches = realloc(*matches, new_capacity * sizeof(char *));
            if (!new_matches) {
                for (size_t i = 0; i < count; i++) {
                    free((*matches)[i]);
                }
                free(*matches);
                *matches = NULL;
                regfree(&regex);
                return -1;
            }
            *matches = new_matches;
            capacity = new_capacity;
        }
        
        if (len > 0) {
            (*matches)[count] = malloc(len + 1);
            if (!(*matches)[count]) {
                for (size_t i = 0; i < count; i++) {
                    free((*matches)[i]);
                }
                free(*matches);
                *matches = NULL;
                regfree(&regex);
                return -1;
            }
            
            /* Possible weaknesses found:
             *  chained comparison 'X <= Y <= Z' does not behave the same as a mathematical expression [-Wparentheses]
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (len <= (size_t)(p + pmatch[0].rm_so - input) + len <= strlen(input)) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy((*matches)[count], p + pmatch[0].rm_so, len);
                (*matches)[count][len] = '\0';
                count++;
            } else {
                free((*matches)[count]);
                for (size_t i = 0; i < count; i++) {
                    free((*matches)[i]);
                }
                free(*matches);
                *matches = NULL;
                regfree(&regex);
                return -1;
            }
        }
        
        if (pmatch[0].rm_eo == 0) {
            p++;
        } else {
            p += pmatch[0].rm_eo;
        }
    }
    
    *match_count = count;
    regfree(&regex);
    return 0;
}

int main(void) {
    const char *text = "hello_world test_123 abc_def foo_bar x_y z";
    char **matches;
    size_t match_count;
    int result;
    
    result = find_lowercase_underscore_sequences(text, &matches, &match_count);
    
    if (result == 0) {
        printf("Found %zu matches:\n", match_count);
        for (size_t i = 0; i < match_count; i++) {
            printf("%s\n", matches[i]);
            free(matches[i]);
        }
        free(matches);
    } else {
        printf("Error occurred\n");
    }
    
    return 0;
}