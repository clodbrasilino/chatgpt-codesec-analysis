#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char **split_string(const char *input, const char *delimiters, int *count) {
    regex_t re;
    regmatch_t matches[10];
    char *str, *p;
    int i, m;
    char **result;

    if (regcomp(&re, delimiters, REG_EXTENDED | REG_NEWLINE)) return NULL;

    str = strdup(input);
    if (str == NULL) return NULL;

    *count = 1;
    m = regexec(&re, str, 9, matches, 0);
    while (m == 0) {
        (*count)++;
        m = regexec(&re, str + matches[0].rm_eo, 9, matches, 0);
    }

    result = malloc(*count * sizeof(char *));
    p = strtok(str, delimiters);
    for (i = 0; p != NULL && i < *count; i++) {
        size_t len = strlen(p);
        result[i] = malloc((len + 1) * sizeof(char));
        strncpy(result[i], p, len);
        result[i][len] = '\0';
        p = strtok(NULL, delimiters);
    }

    free(str);
    regfree(&re);
    return result;
}

int main() {
    const char *input = "apple,banana;orange:lemon";
    const char *delimiters = ",;:";
    int count;

    char **result = split_string(input, delimiters, &count);

    if (result != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}