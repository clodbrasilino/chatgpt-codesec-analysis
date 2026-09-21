#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_at_uppercase(const char *input, char ***result, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    int match_count, start = 0, len;

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return;
    }

    len = (int)strlen(input);
    *result = (char **)malloc((len + 1) * sizeof(char *));
    if (*result == NULL) {
        regfree(&regex);
        return;
    }
    *count = 0;

    while (start < len && (match_count = regexec(&regex, input + start, 1, matches, 0)) == 0) {
        int end = start + matches[0].rm_so;
        size_t token_len = (size_t)(end - start);
        char *token = (char *)malloc(token_len + 1);
        if (token == NULL) {
            for (int i = 0; i < *count; ++i) {
                free((*result)[i]);
            }
            free(*result);
            regfree(&regex);
            return;
        }
        memcpy(token, input + start, token_len);
        token[token_len] = '\0';
        (*result)[(*count)++] = token;
        start += matches[0].rm_eo;
    }

    if (start < len) {
        size_t token_len = (size_t)(len - start);
        char *token = (char *)malloc(token_len + 1);
        if (token == NULL) {
            for (int i = 0; i < *count; ++i) {
                free((*result)[i]);
            }
            free(*result);
            regfree(&regex);
            return;
        }
        memcpy(token, input + start, token_len);
        token[token_len] = '\0';
        (*result)[(*count)++] = token;
    }

    regfree(&regex);
}

int main() {
    const char *input = "HelloWorldExample";
    int count = 0;
    char **result = NULL;

    split_string_at_uppercase(input, &result, &count);

    for (int i = 0; i < count; ++i) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}