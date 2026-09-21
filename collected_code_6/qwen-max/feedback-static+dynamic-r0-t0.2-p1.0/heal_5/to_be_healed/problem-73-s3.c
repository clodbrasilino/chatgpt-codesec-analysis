#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string(const char *input, const char *delimiters, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    const char *str = input;
    /* Possible weaknesses found:
     *  p is initialized
     */
    const char *p = str;
    size_t len, match_count = 0, i;

    if (regcomp(&regex, delimiters, REG_EXTENDED|REG_NEWLINE)) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strnlen(str, strlen(input) + 1);
    *count = 0;
    for (i = 0; i <= len; i++) {
        if (regexec(&regex, str + i, 1, matches, 0) == 0) {
            match_count++;
            i += matches[0].rm_eo - 1;
        }
    }

    *count = match_count + 1;
    char **result = malloc((*count) * sizeof(char *));
    if (!result) {
        regfree(&regex);
        return NULL;
    }

    /* Possible weaknesses found:
     *  Redundant initialization for 'p'. The initialized value is overwritten before it is read. [redundantInitialization]
     *  p is overwritten
     */
    p = strdup(input);
    if (!p) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    str = p;
    for (i = 0; i < *count; i++) {
        result[i] = p;
        if (i < *count - 1 && regexec(&regex, p, 1, matches, 0) == 0) {
            p += matches[0].rm_eo;
            /* Possible weaknesses found:
             *  read-only variable is not assignable
             *  assignment of read-only location '*p++'
             */
            *p++ = '\0';
        }
    }

    regfree(&regex);
    return result;
}

int main() {
    const char *input = "apple,orange;banana:grape";
    const char *delimiters = ",;:";
    int count;
    char **result = split_string(input, delimiters, &count);

    if (result) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", result[i]);
        }
        free(result[0]);
        free(result);
    }

    return 0;
}