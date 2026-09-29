#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string(const char *input, const char *delimiters, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    char *str, *p;
    int len, match_count = 0, i;

    if (regcomp(&regex, delimiters, REG_EXTENDED|REG_NEWLINE)) {
        return NULL;
    }

    str = strdup(input);
    if (!str) {
        regfree(&regex);
        return NULL;
    }

    len = strlen(str);
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
        free(str);
        regfree(&regex);
        return NULL;
    }

    p = str;
    for (i = 0; i < *count; i++) {
        result[i] = p;
        if (i < *count - 1 && regexec(&regex, p, 1, matches, 0) == 0) {
            p += matches[0].rm_eo;
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
            free(result[i]);
        }
        free(result);
    }

    return 0;
}