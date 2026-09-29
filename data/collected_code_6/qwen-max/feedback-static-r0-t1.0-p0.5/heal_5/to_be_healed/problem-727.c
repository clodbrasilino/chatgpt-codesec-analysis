#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void sanitize_string(char *str) {
    regex_t regex;
    regmatch_t match[1];
    size_t len = 0, new_len = 0;
    char *p, *end, *new_str;

    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    new_str = malloc(len + 1);
    if (!new_str) {
        return;
    }

    end = str + len;
    p = str;
    while (p < end) {
        if (regexec(&regex, p, 1, match, 0) == 0) {
            p += match[0].rm_eo;
        } else {
            new_str[new_len++] = *p++;
        }
    }
    new_str[new_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, new_str);
    free(new_str);
    regfree(&regex);
}

int main() {
    char input[] = "Hello, World! 123";
    sanitize_string(input);
    printf("%s\n", input);
    return 0;
}