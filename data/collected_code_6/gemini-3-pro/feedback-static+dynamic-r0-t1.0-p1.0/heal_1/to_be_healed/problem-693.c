#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_multiple_spaces(char *str) {
    if (str == NULL) {
        return -1;
    }

    regex_t regex;
    int reti;
    regmatch_t pmatch[1];
    char *pattern = "  +";
    char *temp_str = NULL;
    size_t len;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str) + 1;
    temp_str = (char *)malloc(len);
    if (temp_str == NULL) {
        regfree(&regex);
        return -1;
    }

    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(temp_str, str, start + 1);
        temp_str[start + 1] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(temp_str, str + end);
        
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(str, temp_str);
    }

    free(temp_str);
    regfree(&regex);
    return 0;
}

int main(void) {
    char test_string[] = "This    is  a   test      string  with    multiple     spaces.";
    
    printf("Original: '%s'\n", test_string);
    
    if (remove_multiple_spaces(test_string) == 0) {
        printf("Modified: '%s'\n", test_string);
    } else {
        printf("Error processing string.\n");
    }
    
    return 0;
}