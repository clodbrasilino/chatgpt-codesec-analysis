#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_non_alphanumeric(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t match;
    const char* pattern = "[^a-zA-Z0-9]";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }
    
    size_t src_pos = 0;
    size_t dst_pos = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ret' can be reduced. [variableScope]
     */
    int ret;
    
    while (src_pos < len) {
        ret = regexec(&regex, input + src_pos, 1, &match, 0);
        if (ret != 0) {
            size_t remaining = len - src_pos;
            if (dst_pos + remaining >= len + 1) {
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
            if (dst_pos + match_start >= len + 1) {
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
    
    if (dst_pos >= len + 1) {
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