#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void extract_quoted_values(const char *str) {
    if (!str) return;

    regex_t regex;
    regmatch_t pmatch[2];
    int status;
    const char *pattern = "\"([^\"]*)\"";

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return;
    }

    const char *cursor = str;
    /* Possible weaknesses found:
     *  Although the value stored to 'status' is used in the enclosing expression, the value is never actually read from 'status' [deadcode.DeadStores]
     */
    while ((status = regexec(&regex, cursor, 2, pmatch, 0)) == 0) {
        regoff_t start = pmatch[1].rm_so;
        regoff_t end = pmatch[1].rm_eo;

        if (start != -1 && end != -1) {
            size_t len = end - start;
            char *value = malloc(len + 1);
            if (value) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(value, cursor + start, len);
                value[len] = '\0';
                printf("%s\n", value);
                free(value);
            } else {
                regfree(&regex);
                return;
            }
        }
        cursor += pmatch[0].rm_eo;
    }

    regfree(&regex);
}

int main(void) {
    const char *test_str = "This is a \"test\" string with \"multiple\" quoted \"values\".";
    extract_quoted_values(test_str);
    return 0;
}