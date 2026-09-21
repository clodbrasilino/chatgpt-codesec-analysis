#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_multiple_spaces(char **str) {
    if (str == NULL || *str == NULL) {
        return -1;
    }

    regex_t regex;
    int reti;

    reti = regcomp(&regex, "  +", REG_EXTENDED);
    if (reti) {
        return -1;
    }

    regmatch_t pmatch[1];
    char *current = *str;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t new_len = strlen(current);
    char *new_str = malloc(new_len + 1);

    if (new_str == NULL) {
        regfree(&regex);
        return -1;
    }

    char *dest = new_str;

    while (regexec(&regex, current, 1, pmatch, 0) == 0) {
        size_t copy_len = pmatch[0].rm_so;
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, current, copy_len);
        dest += copy_len;
        
        *dest = ' ';
        dest++;
        
        current += pmatch[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(dest, current);

    free(*str);
    *str = new_str;

    regfree(&regex);
    return 0;
}

int main(void) {
    char *text = strdup("This   is  a    test string   with multiple     spaces.");
    if (text == NULL) {
        return 1;
    }

    printf("Original: '%s'\n", text);

    if (remove_multiple_spaces(&text) == 0) {
        printf("Modified: '%s'\n", text);
    } else {
        printf("Error processing string.\n");
    }

    free(text);
    return 0;
}