#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int i = 0;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED)) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    char *new_str = malloc(str_len + 1);
    if (!new_str) {
        regfree(&regex);
        return;
    }
    new_str[str_len] = '\0';

    size_t n_pos = 0;
    while (1) {
        int rc = regexec(&regex, str + i, 1, pmatch, 0);
        if (rc == REG_NOMATCH) break;
        if (rc != 0) {
            free(new_str);
            regfree(&regex);
            return;
        }
        size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        if (match_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(new_str + n_pos, str + i, match_len);
            new_str[n_pos + match_len] = ':';
            n_pos += match_len + 1;
            i += match_len;
        } else {
            new_str[n_pos++] = str[i++];
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(new_str + n_pos, str + i, str_len - i + 1);
    new_str[str_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, new_str);
    free(new_str);
    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}