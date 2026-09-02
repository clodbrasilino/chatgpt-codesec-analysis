#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char **extract_quoted_values(const char *input, int *count) {
    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "\"([^\"]*)\"";
    char *str = (char *)input;
    char **result = NULL;
    *count = 0;

    if (regcomp(&regex, pattern, REG_EXTENDED|REG_NEWLINE) != 0) {
        return NULL;
    }

    while (regexec(&regex, str, 2, matches, 0) == 0) {
        char **new_result = realloc(result, (*count + 1) * sizeof(char *));
        if (new_result == NULL) {
            for (int i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }
        result = new_result;
        result[*count] = malloc(matches[1].rm_eo - matches[1].rm_so + 1);
        if (result[*count] == NULL) {
            for (int i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result[*count], &str[matches[1].rm_so], matches[1].rm_eo - matches[1].rm_so);
        result[*count][matches[1].rm_eo - matches[1].rm_so] = '\0';
        *count += 1;
        str += matches[0].rm_eo;
    }

    regfree(&regex);
    return result;
}

int main() {
    const char *input = "This is a \"test\" string with multiple \"quoted values\".";
    int count;
    char **values = extract_quoted_values(input, &count);

    if (values != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", values[i]);
            free(values[i]);
        }
        free(values);
    }

    return 0;
}