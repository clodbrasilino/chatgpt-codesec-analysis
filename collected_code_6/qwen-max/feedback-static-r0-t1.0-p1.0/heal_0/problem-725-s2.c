#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void extract_quoted_values(const char *input, char ***values, int *count) {
    *count = 0;
    regex_t regex;
    regmatch_t matches[2];
    char *str_copy = strdup(input);
    
    if (regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED) != 0) {
        free(str_copy);
        return;
    }

    while (regexec(&regex, str_copy, 2, matches, 0) == 0) {
        (*count)++;
        str_copy[matches[0].rm_eo] = '\0';
        str_copy += matches[0].rm_eo;
    }

    *values = (char **)malloc((*count) * sizeof(char *));
    if (*values == NULL) {
        regfree(&regex);
        free(str_copy);
        return;
    }

    regfree(&regex);
    regex_t new_regex;
    if (regcomp(&new_regex, "\"([^\"]*)\"", REG_EXTENDED) != 0) {
        free(*values);
        free(str_copy);
        return;
    }

    int i = 0;
    str_copy = strdup(input);

    while (regexec(&new_regex, str_copy, 2, matches, 0) == 0) {
        int len = matches[1].rm_eo - matches[1].rm_so;
        (*values)[i] = (char *)malloc((len + 1) * sizeof(char));
        if ((*values)[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free((*values)[j]);
            }
            free(*values);
            free(str_copy);
            regfree(&new_regex);
            return;
        }
        strncpy((*values)[i], str_copy + matches[1].rm_so, len);
        (*values)[i][len] = '\0';
        str_copy[matches[0].rm_eo] = '\0';
        str_copy += matches[0].rm_eo;
        i++;
    }

    regfree(&new_regex);
    free(str_copy);
}

int main() {
    const char *input = "This is a \"test\" string with multiple \"quotes\".";
    char **values;
    int count;

    extract_quoted_values(input, &values, &count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", values[i]);
        free(values[i]);
    }

    free(values);
    return 0;
}