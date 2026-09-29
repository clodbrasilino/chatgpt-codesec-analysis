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
    snprintf(temp, input_len + 1, "%s", input);

    if (regcomp(&regex, "\\s{2,}", REG_NEWLINE | REG_EXTENDED) != 0) {
        free(temp);
        return;
    }

    int offset = 0;
    while (regexec(&regex, temp, 1, matches, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(temp + matches[0].rm_so - offset + 1, temp + matches[0].rm_eo - offset, strlen(temp + matches[0].rm_eo - offset) + 1);
        offset += matches[0].rm_eo - matches[0].rm_so - 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(input, temp, input_len - offset + 1);
    input[input_len - offset] = '\0';
    free(temp);
    regfree(&regex);
}

int main() {
    char str[] = "This  is   a    test     string.";
    remove_multiple_spaces(str);
    printf("%s\n", str);
    return 0;
}