#include <stdio.h>
#include <regex.h>
#include <string.h>

void replace_chars(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256] = {0};
    /* Possible weaknesses found:
     *  The scope of the variable 'rc' can be reduced. [variableScope]
     */
    int rc, i = 0;

    if (regcomp(&regex, "[ ,.]", REG_EXTENDED)) return;

    while (1) {
        rc = regexec(&regex, str + i, 1, pmatch, 0);
        if (rc == REG_NOMATCH || pmatch[0].rm_so == -1) break;

        size_t len = pmatch[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (len + 1 + strlen(str + i + pmatch[0].rm_eo) < sizeof(buffer)) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(buffer, str + i, len);
            buffer[len] = ':';
            buffer[len + 1] = '\0';
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(buffer, str + i + pmatch[0].rm_eo, sizeof(buffer) - len - 2);
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(str + i, buffer);
        }

        i += pmatch[0].rm_so + 1;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello, World. This is a test string.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}