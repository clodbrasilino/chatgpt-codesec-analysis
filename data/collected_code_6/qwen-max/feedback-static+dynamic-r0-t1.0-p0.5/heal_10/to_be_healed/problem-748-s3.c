#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void add_spaces_between_capital_letters(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "([a-z])([A-Z])";

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        return;
    }

    int pos = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *new_str = malloc(len * 2 + 1); // Allocate memory for the new string
    if (!new_str) {
        regfree(&regex);
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(new_str, str);

    while (regexec(&regex, new_str + pos, 1, match, 0) == 0) {
        int start = pos + match[0].rm_so;
        int end = pos + match[0].rm_eo;

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(new_str + start + 2, new_str + start, strlen(new_str + start) + 1);
        new_str[start] = ' ';
        new_str[start + 1] = new_str[end];
        pos = start + 2;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, new_str, len * 2 + 1);
    free(new_str);
    regfree(&regex);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    add_spaces_between_capital_letters(input);
    printf("%s\n", input);
    return 0;
}