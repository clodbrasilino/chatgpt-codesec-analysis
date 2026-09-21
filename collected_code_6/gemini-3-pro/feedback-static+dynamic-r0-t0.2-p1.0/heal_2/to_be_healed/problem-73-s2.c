#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_by_regex(const char *str, const char *pattern) {
    regex_t regex;
    regmatch_t pmatch[1];
    int status;
    const char *cursor = str;

    if (str == NULL || pattern == NULL) {
        return;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return;
    }

    while (1) {
        status = regexec(&regex, cursor, 1, pmatch, 0);
        if (status == 0) {
            int len = pmatch[0].rm_so;
            if (len > 0) {
                char *token = (char *)malloc(len + 1);
                if (token != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(token, cursor, len);
                    token[len] = '\0';
                    printf("%s\n", token);
                    free(token);
                }
            }
            cursor += pmatch[0].rm_eo;
        } else {
            if (*cursor != '\0') {
                printf("%s\n", cursor);
            }
            break;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "apple,banana;cherry|date orange";
    const char *pattern = "[,;| ]+";

    split_string_by_regex(text, pattern);

    return 0;
}