#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Quad Core', got <no output>
  *  test case 2 failed: expected 'ChromeCast Built-in', got <no output>
  *  test case 0 failed: expected 'Google Assistant', got <no output>
  */

char *remove_multiple_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }
    
    regex_t regex;
    int ret = regcomp(&regex, " +", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }
    
    size_t input_len = strnlen(input, 65536);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    
    const char *src = input;
    char *dst = result;
    size_t dst_remaining = input_len;
    regmatch_t match;
    
    while (regexec(&regex, src, 1, &match, 0) == 0) {
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;
        
        if (match_start > 0) {
            if (match_start > dst_remaining) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dst, src, match_start);
            dst += match_start;
            dst_remaining -= match_start;
        }
        
        if (dst_remaining < 1) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        *dst++ = ' ';
        dst_remaining--;
        
        src += match_end;
    }
    
    size_t remaining = strnlen(src, 65536 - (src - input));
    if (remaining + 1 > dst_remaining) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst, src, remaining + 1);
    
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "Google  Assistant",
        "Quad   Core",
        "ChromeCast    Built-in"
    };
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < num_tests; i++) {
        char *cleaned = remove_multiple_spaces(test_cases[i]);
        
        if (cleaned != NULL) {
            printf("%s\n", cleaned);
            free(cleaned);
        } else {
            fprintf(stderr, "Error processing string\n");
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}