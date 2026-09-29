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
    /* Possible weaknesses found:
     *  The scope of the variable 'last_end' can be reduced. [variableScope]
     *  Variable 'last_end' is assigned a value that is never used. [unreadVariable]
     */
    int last_end = 0;
    
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
        /* Possible weaknesses found:
         *  Value stored to 'last_end' is never read [deadcode.DeadStores]
         *  Variable 'last_end' is assigned a value that is never used. [unreadVariable]
         */
        last_end = match_end;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(dst, src);
    
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test = "This  is   a    test   string";
    char *cleaned = remove_multiple_spaces(test);
    
    if (cleaned != NULL) {
        printf("Original: '%s'\n", test);
        printf("Cleaned:  '%s'\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}