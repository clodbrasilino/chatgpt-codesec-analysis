#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_at_uppercase(const char *input, char ***result, int *count) {
    regex_t regex;
    regmatch_t matches[20];
    char *str, *p;
    int num_tokens = 0;

    if (regcomp(&regex, "[A-Z][^A-Z]*", REG_EXTENDED) != 0) {
        return;
    }

    str = strdup(input);
    p = str;

    while (regexec(&regex, p, 20, matches, 0) == 0) {
        num_tokens++;
        p += matches[0].rm_eo;
    }

    *result = (char **)malloc(num_tokens * sizeof(char *));
    *count = num_tokens;

    p = str;
    for (int i = 0; i < num_tokens; i++) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        (*result)[i] = (char *)malloc(matches[0].rm_eo - matches[0].rm_so + 1);
        for (int j = 0; j < matches[0].rm_eo - matches[0].rm_so; j++) {
            (*result)[i][j] = p[matches[0].rm_so + j];
        }
        (*result)[i][matches[0].rm_eo - matches[0].rm_so] = '\0';
        p += matches[0].rm_eo;
        regexec(&regex, p, 20, matches, 0);
    }

    free(str);
    regfree(&regex);
}

int main() {
    const char *input = "HelloWorldExample";
    char **result;
    int count;

    split_string_at_uppercase(input, &result, &count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);

    return 0;
}