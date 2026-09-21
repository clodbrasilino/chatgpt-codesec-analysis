#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void remove_multiple_spaces(char *input) {
    regex_t regex;
    regmatch_t matches[1];
    size_t input_len = strnlen(input, 4096);
    char *temp = malloc(input_len + 1);
    if (temp == NULL) {
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp, input, input_len);
    temp[input_len] = '\0';

    if (regcomp(&regex, "\\s{2,}", REG_NEWLINE | REG_EXTENDED) != 0) {
        free(temp);
        return;
    }

    while (regexec(&regex, temp, 1, matches, 0) == 0) {
        memmove(temp + matches[0].rm_so + 1, temp + matches[0].rm_eo, input_len - matches[0].rm_eo + 1);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        input_len = strlen(temp);
        temp[input_len] = '\0';
    }

    if (snprintf(input, input_len + 1, "%s", temp) >= 0) {
        free(temp);
        regfree(&regex);
    } else {
        free(temp);
    }
}

int main() {
    char str[] = "This  is   a    test     string.";
    remove_multiple_spaces(str);
    printf("%s\n", str);
    return 0;
}