#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void extract_quoted_values(const char *input_string) {
    if (input_string == NULL) {
        return;
    }

    regex_t regex;
    regmatch_t pmatch[2];
    const char *pattern = "\"([^\"]*)\"";
    const char *cursor = input_string;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return;
    }

    /* Possible weaknesses found:
     *  Although the value stored to 'status' is used in the enclosing expression, the value is never actually read from 'status' [deadcode.DeadStores]
     */
    while ((status = regexec(&regex, cursor, 2, pmatch, 0)) == 0) {
        if (pmatch[1].rm_so == -1) {
            break;
        }

        regoff_t start = pmatch[1].rm_so;
        regoff_t end = pmatch[1].rm_eo;
        size_t len = (size_t)(end - start);

        char *value = (char *)malloc(len + 1);
        if (value != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(value, cursor + start, len);
            value[len] = '\0';
            printf("%s\n", value);
            free(value);
        }

        cursor += pmatch[0].rm_eo;
    }

    regfree(&regex);
}

int main(void) {
    const char *test_string = "This is a \"test\" string with \"multiple\" quoted \"values\".";
    extract_quoted_values(test_string);
    return 0;
}