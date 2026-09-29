#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_multiple_spaces(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int ret = regcomp(&regex, "  +", REG_EXTENDED);
    if (ret != 0) {
        return;
    }

    regmatch_t pmatch[1];
    char *cursor = str;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *temp = malloc(strlen(str) + 1);
    
    if (temp == NULL) {
        regfree(&regex);
        return;
    }

    temp[0] = '\0';
    size_t temp_len = 0;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(temp + temp_len, cursor, pmatch[0].rm_so);
        temp_len += pmatch[0].rm_so;
        
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strcat(temp + temp_len, " ");
        temp_len += 1;
        
        cursor += pmatch[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(temp + temp_len, cursor);
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, temp);

    free(temp);
    regfree(&regex);
}

int main(void) {
    char str[] = "This   is   a    string    with    multiple   spaces.";
    
    remove_multiple_spaces(str);
    
    printf("%s\n", str);
    
    return 0;
}