#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_at_uppercase(const char *input, char ***result, int *count) {
    regex_t regex;
    regmatch_t matches[20];
    int i;
    char *str, *p;

    if (regcomp(&regex, "[A-Z][^A-Z]*", REG_EXTENDED)) {
        return;
    }

    str = strdup(input);
    p = str;

    *count = 0;

    while (regexec(&regex, p, 20, matches, 0) == 0) {
        (*count)++;
        p += matches[0].rm_eo;
    }

    *result = (char **)malloc((*count) * sizeof(char *));
    for (i = 0; i < *count; i++) {
        (*result)[i] = NULL;
    }

    p = str;
    for (i = 0; i < *count; i++) {
        if (regexec(&regex, p, 20, matches, 0) == 0) {
            size_t len = matches[0].rm_eo - matches[0].rm_so;
            (*result)[i] = (char *)malloc(len + 1);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy((*result)[i], p + matches[0].rm_so, len);
            (*result)[i][len] = '\0';
            p += matches[0].rm_eo;
        }
    }

    free(str);
    regfree(&regex);
}

int main() {
    const char *input = "HelloWorldExample";
    char **result = NULL;
    int count = 0;

    split_string_at_uppercase(input, &result, &count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}