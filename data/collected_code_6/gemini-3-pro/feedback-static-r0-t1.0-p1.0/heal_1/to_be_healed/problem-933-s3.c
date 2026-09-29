#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* camel_to_snake(const char *input) {
    if (!input) return NULL;

    regex_t regex;
    int ret = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t out_size = strlen(input) * 2 + 1;
    char *result = (char*)malloc(out_size);
    if (!result) {
        regfree(&regex);
        return NULL;
    }

    const char *p = input;
    char *q = result;
    regmatch_t pmatch[3];

    while (regexec(&regex, p, 3, pmatch, 0) == 0) {
        size_t len = pmatch[1].rm_eo;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(q, p, len);
        q += len;
        
        *q++ = '_';
        *q++ = p[pmatch[2].rm_so] + 32;
        
        p += pmatch[2].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(q, p);
    regfree(&regex);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *final_result = (char*)realloc(result, strlen(result) + 1);
    if (!final_result) {
        return result; 
    }
    
    return final_result;
}

int main(void) {
    const char *test_str = "camelCaseStringExample";
    char *snake_str = camel_to_snake(test_str);
    
    if (snake_str) {
        printf("%s\n", snake_str);
        free(snake_str);
    }
    
    return 0;
}