#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void remove_multiple_spaces(char *input) {
    regex_t regex;
    regmatch_t matches[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *temp = malloc(strlen(input) + 1);
    if (temp == NULL) {
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(temp, input);

    if (regcomp(&regex, "\\s{2,}", REG_NEWLINE | REG_EXTENDED) != 0) {
        free(temp);
        return;
    }

    while (regexec(&regex, temp, 1, matches, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(temp + matches[0].rm_so + 1, temp + matches[0].rm_eo, strlen(temp + matches[0].rm_eo) + 1);
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'str' undeclared (first use in this function)
     *  use of undeclared identifier 'str'
     */
    snprintf(input, sizeof(str), "%s", temp);
    free(temp);
    regfree(&regex);
}

int main() {
    char str[] = "This  is   a    test     string.";
    remove_multiple_spaces(str);
    printf("%s\n", str);
    return 0;
}