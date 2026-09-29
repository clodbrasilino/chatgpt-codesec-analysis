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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    
    const char *src = input;
    char *dst = result;
    regmatch_t match;
    
    while (regexec(&regex, src, 1, &match, 0) == 0) {
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;
        
        if (match_start > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dst, src, match_start);
            dst += match_start;
        }
        
        *dst++ = ' ';
        
        src += match_end;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining = strlen(src);
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