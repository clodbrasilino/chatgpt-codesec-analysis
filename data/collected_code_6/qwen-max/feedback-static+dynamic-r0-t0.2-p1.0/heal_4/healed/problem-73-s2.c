#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char **split_string(const char *input, const char *delimiters, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    char *str, *p;
    size_t i, nmatches;
    char **result;

    if (regcomp(&regex, delimiters, REG_EXTENDED|REG_NEWLINE) != 0) {
        return NULL;
    }

    str = strdup(input);
    if (!str) {
        regfree(&regex);
        return NULL;
    }

    *count = 0;

    for (i = 0; str[i] != '\0'; i++) {
        nmatches = regexec(&regex, str + i, 1, matches, 0);
        if (nmatches == 0 && matches[0].rm_so == 0) {
            *count += 1;
            i += matches[0].rm_eo - 1;
        }
    }

    result = malloc((*count + 1) * sizeof(char *));
    if (!result) {
        free(str);
        regfree(&regex);
        return NULL;
    }

    p = str;
    for (i = 0; i < *count; i++) {
        nmatches = regexec(&regex, p, 1, matches, 0);
        if (nmatches == 0 && matches[0].rm_so == 0) {
            result[i] = strndup(p, matches[0].rm_so);
            p += matches[0].rm_eo;
        } else {
            size_t len = strlen(p);
            result[i] = strndup(p, len ? len : 1);
            break;
        }
    }
    result[*count] = NULL;

    free(str);
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