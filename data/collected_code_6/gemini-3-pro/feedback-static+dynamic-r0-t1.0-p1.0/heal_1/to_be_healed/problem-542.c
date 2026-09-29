#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* replace_chars(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti;
    const char* pattern = "[ ,.]";
    
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char* p = input;
    char* q = result;
    regmatch_t pmatch[1];

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        size_t match_len = pmatch[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(q, p, match_len);
        q += match_len;
        *q = ':';
        q++;
        p += pmatch[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(q, p);

    regfree(&regex);
    return result;
}

int main(void) {
    const char* original_str = "Hello, world. This is a test string.";
    
    char* modified_str = replace_chars(original_str);
    
    if (modified_str != NULL) {
        printf("Original: %s\n", original_str);
        printf("Modified: %s\n", modified_str);
        
        free(modified_str);
    } else {
        printf("An error occurred during replacement.\n");
    }

    return 0;
}