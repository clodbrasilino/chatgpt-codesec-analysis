#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_regex(const char *str, const char *pattern) {
    if (str == NULL || pattern == NULL) {
        return;
    }

    regex_t regex;
    int reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return;
    }

    regmatch_t pmatch[1];
    const char *p = str;

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        regoff_t len = pmatch[0].rm_so;
        if (len > 0) {
            char *token = (char *)malloc(len + 1);
            if (token != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(token, p, len);
                token[len] = '\0';
                printf("'%s'\n", token);
                free(token);
            }
        }
        p += pmatch[0].rm_eo;
    }

    if (*p != '\0') {
        printf("'%s'\n", p);
    }

    regfree(&regex);
}

int main(void) {
    const char *str = "Hello, world! This is a test; let's split this string.";
    const char *pattern = "[,! ;]+"; 

    split_string_regex(str, pattern);

    return 0;
}