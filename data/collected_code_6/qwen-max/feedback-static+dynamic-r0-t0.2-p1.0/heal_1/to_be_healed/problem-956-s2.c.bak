#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_at_uppercase(const char *input, char ***result, int *count) {
    regex_t regex;
    regmatch_t matches[10];
    /* Possible weaknesses found:
     *  Unused variable: j [unusedVariable]
     *  Unused variable: match_count [unusedVariable]
     */
    int match_count, i, j, start, end, len, index = 0;
    char *str, *token;

    if (regcomp(&regex, "([A-Z][^A-Z]*)", REG_EXTENDED) != 0) {
        return;
    }

    str = strdup(input);
    if (!str) {
        return;
    }

    *count = 0;
    while (regexec(&regex, str + index, 10, matches, 0) == 0) {
        (*count)++;
        for (i = 0; i < 10 && matches[i].rm_so != -1; i++) {
            start = matches[i].rm_so + index;
            end = matches[i].rm_eo + index;
            len = end - start;
            token = (char *)malloc(len + 1);
            if (!token) {
                free(str);
                regfree(&regex);
                return;
            }
            strncpy(token, str + start, len);
            token[len] = '\0';
            (*result) = (char **)realloc(*result, (*count) * sizeof(char *));
            if (!*result) {
                free(token);
                free(str);
                regfree(&regex);
                return;
            }
            (*result)[(*count) - 1] = token;
            index = end;
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