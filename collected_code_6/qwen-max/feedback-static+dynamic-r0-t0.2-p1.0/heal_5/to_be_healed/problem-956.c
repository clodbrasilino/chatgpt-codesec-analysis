#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void split_string_at_uppercase(const char *input, char ***result, int *count) {
    regex_t regex;
    regmatch_t matches[20];
    /* Possible weaknesses found:
     *  Unused variable: j [unusedVariable]
     */
    int i, j;
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

    *count = num_tokens;
    *result = (char **)malloc(num_tokens * sizeof(char *));

    p = str;
    for (i = 0; i < num_tokens; i++) {
        (*result)[i] = (char *)malloc(matches[0].rm_eo - matches[0].rm_so + 1);
        /* Possible weaknesses found:
         * ASan: heap-buffer-overflow
         */
        strncpy((*result)[i], p + matches[0].rm_so, matches[0].rm_eo - matches[0].rm_so);
        (*result)[i][matches[0].rm_eo - matches[0].rm_so] = '\0';
        p += matches[0].rm_eo;
        if (i < num_tokens - 1) {
            regexec(&regex, p, 20, matches, 0);
        }
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