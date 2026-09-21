#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_at_uppercase(const char *input, char ***result, int *count) {
    regex_t regex;
    regmatch_t matches[20];
    int i, j, k;
    char *str, *p;

    if (regcomp(&regex, "[A-Z][^A-Z]*", REG_EXTENDED) != 0) {
        return;
    }

    str = strdup(input);
    p = str;

    *count = 0;

    while (regexec(&regex, p, 20, matches, 0) == 0) {
        (*count)++;
        p += matches[0].rm_eo;
    }

    *result = (char **)malloc((*count) * sizeof(char *));
    for (i = 0; i < *count; i++) {
        (*result)[i] = NULL;
    }

    p = str;
    for (i = 0; i < *count; i++) {
        if (regexec(&regex, p, 20, matches, 0) == 0) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            (*result)[i] = (char *)malloc(matches[0].rm_eo - matches[0].rm_so + 1);
            for (j = 0, k = 0; j < matches[0].rm_eo - matches[0].rm_so; j++, k++) {
                (*result)[i][k] = p[matches[0].rm_so + j];
            }
            (*result)[i][k] = '\0';
            p += matches[0].rm_eo;
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