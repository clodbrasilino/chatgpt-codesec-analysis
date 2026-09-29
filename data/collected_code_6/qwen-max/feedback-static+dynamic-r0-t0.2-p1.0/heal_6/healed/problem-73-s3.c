#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string(const char *input, const char *delimiters, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    size_t len, match_count = 0, i;

    if (regcomp(&regex, delimiters, REG_EXTENDED|REG_NEWLINE)) {
        return NULL;
    }

    len = strnlen(input, strlen(input) + 1);
    *count = 0;
    for (i = 0; i < len; i++) {
        if (regexec(&regex, input + i, 1, matches, 0) == 0) {
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

    char *p = strdup(input);
    if (!p) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    char *str = p;
    for (i = 0; i < *count - 1; i++) {
        result[i] = str;
        if (regexec(&regex, str, 1, matches, 0) == 0) {
            str += matches[0].rm_eo;
            *str++ = '\0';
        }
    }
    result[*count - 1] = str;

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