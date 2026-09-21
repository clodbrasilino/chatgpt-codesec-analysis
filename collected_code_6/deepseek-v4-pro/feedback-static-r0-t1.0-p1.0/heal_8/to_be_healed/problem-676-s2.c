#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_non_alphanumeric(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, 65536);
    
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';
    
    regex_t regex;
    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }
    
    size_t src_pos = 0;
    size_t dst_pos = 0;
    regmatch_t match;
    
    while (src_pos < len) {
        int ret = regexec(&regex, input + src_pos, 1, &match, 0);
        if (ret != 0) {
            size_t remaining = len - src_pos;
            if (dst_pos + remaining > len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, input + src_pos, remaining);
            dst_pos += remaining;
            break;
        }
        
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;
        
        if (match_start > 0) {
            if (dst_pos + match_start > len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, input + src_pos, match_start);
            dst_pos += match_start;
        }
        
        src_pos += match_end;
    }
    
    if (dst_pos > len) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    result[dst_pos] = '\0';
    
    regfree(&regex);
    return result;
}

int main(void) {
    const char* test_string = "Hello, World! 123 @#$%^&*()";
    char* cleaned = remove_non_alphanumeric(test_string);
    
    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
        return 1;
    }
    
    return 0;
}