#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string(const char *input, const char *delimiters, char ***result, int *count) {
    regex_t re;
    regmatch_t match[1];
    int status, offset = 0, len, i = 0;

    if (regcomp(&re, delimiters, REG_EXTENDED | REG_NEWLINE) != 0) {
        return;
    }

    *count = 1;
    while ((status = regexec(&re, input + offset, 1, match, 0)) == 0) {
        (*count)++;
        offset += match[0].rm_eo;
    }
    *result = (char **)malloc(*count * sizeof(char *));
    if (*result == NULL) {
        regfree(&re);
        return;
    }

    offset = 0;
    i = 0;
    while (i < *count - 1) {
        len = match[0].rm_so;
        (*result)[i] = (char *)malloc(len + 1);
        if ((*result)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*result)[j]);
            }
            free(*result);
            regfree(&re);
            return;
        }
        strncpy((*result)[i], input + offset, len);
        (*result)[i][len] = '\0';
        offset += match[0].rm_eo;
        i++;
        if (regexec(&re, input + offset, 1, match, 0) != 0) {
            break;
        }
    }
    len = strlen(input + offset);
    (*result)[i] = (char *)malloc(len + 1);
    if ((*result)[i] == NULL) {
        for (int j = 0; j < i; j++) {
            free((*result)[j]);
        }
        free(*result);
        regfree(&re);
        return;
    }
    strncpy((*result)[i], input + offset, len);
    (*result)[i][len] = '\0';

    regfree(&re);
}

int main() {
    const char *input = "apple,orange;banana|grape";
    const char *delimiters = ",;|";
    char **result = NULL;
    int count = 0;

    split_string(input, delimiters, &result, &count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}