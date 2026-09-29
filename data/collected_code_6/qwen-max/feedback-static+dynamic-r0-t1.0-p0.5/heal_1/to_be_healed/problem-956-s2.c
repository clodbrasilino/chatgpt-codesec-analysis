#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_at_uppercase(const char *input, char ***result, int *count) {
    regex_t regex;
    regmatch_t matches[10];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Unused variable: j [unusedVariable]
     *  The scope of the variable 'i' can be reduced. [variableScope]
     *  The scope of the variable 'end' can be reduced. [variableScope]
     */
    int match_count, i, j, start = 0, end, len = strlen(input);
    char *token;
    *count = 0;

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return;
    }

    while (start < len && (match_count = regexec(&regex, input + start, 1, matches, 0)) == 0) {
        end = start + matches[0].rm_so;
        token = (char *)malloc(end - start + 1);
        if (token == NULL) {
            regfree(&regex);
            return;
        }
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(token, input + start, end - start);
        token[end - start] = '\0';
        (*result)[(*count)++] = token;
        start += matches[0].rm_eo;
    }

    token = (char *)malloc(len - start + 1);
    if (token == NULL) {
        for (i = 0; i < *count; ++i) {
            free((*result)[i]);
        }
        free(*result);
        regfree(&regex);
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(token, input + start, len - start);
    token[len - start] = '\0';
    (*result)[(*count)++] = token;

    regfree(&regex);
}

int main() {
    const char *input = "HelloWorldExample";
    int count = 0;
    char **result = (char **)malloc(10 * sizeof(char *));
    if (result == NULL) {
        return 1;
    }

    split_string_at_uppercase(input, &result, &count);

    for (int i = 0; i < count; ++i) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}