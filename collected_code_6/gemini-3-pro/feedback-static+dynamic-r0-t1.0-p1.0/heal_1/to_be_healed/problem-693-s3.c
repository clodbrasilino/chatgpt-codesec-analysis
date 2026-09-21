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

    new_str[0] = '\0';
    /* Possible weaknesses found:
     *  Variable 'offset' is assigned a value that is never used. [unreadVariable]
     */
    size_t offset = 0;

    while (regexec(&regex, current, 1, pmatch, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(new_str, current, pmatch[0].rm_so);
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strcat(new_str, " ");
        current += pmatch[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(new_str, current);

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