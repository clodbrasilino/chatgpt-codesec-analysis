#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_at_uppercase(const char *input, char ***result, int *count) {
    regex_t regex;
    regmatch_t matches[10];
    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return;
    }

    int match_count, start = 0, len = strlen(input);
    *count = 0;

    while (start < len && (match_count = regexec(&regex, input + start, 1, matches, 0)) == 0) {
        int end = start + matches[0].rm_so;
        char *token = (char *)malloc(end - start + 1);
        if (token == NULL) {
            for (int i = 0; i < *count; ++i) {
                free((*result)[i]);
            }
            free(*result);
            regfree(&regex);
            return;
        }
        strncpy(token, input + start, end - start);
        token[end - start] = '\0';
        (*result)[(*count)++] = token;
        start += matches[0].rm_eo;
    }

    char *token = (char *)malloc(len - start + 1);
    if (token == NULL) {
        for (int i = 0; i < *count; ++i) {
            free((*result)[i]);
        }
        free(*result);
        regfree(&regex);
        return;
    }
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