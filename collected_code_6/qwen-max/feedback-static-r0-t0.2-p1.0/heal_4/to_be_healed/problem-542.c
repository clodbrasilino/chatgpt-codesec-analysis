#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    char *new_str = (char *)malloc(str_len + 2);
    
    if (!new_str) {
        return;
    }
    new_str[0] = '\0';

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        free(new_str);
        return;
    }

    size_t j = 0;

    while (1) {
        int rc = regexec(&regex, str + j, 1, pmatch, 0);
        if (rc == REG_NOMATCH || pmatch[0].rm_so == -1) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(new_str, str + j, str_len - j + 1);
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(new_str, str + j, pmatch[0].rm_so - j);
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
         */
        strncat(new_str, ":", 1);

        j += pmatch[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, new_str, str_len + 1);
    str[str_len + 1] = '\0';
    free(new_str);
    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}