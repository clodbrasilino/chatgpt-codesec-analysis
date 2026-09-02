#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *camel_to_snake(const char *s) {
    int n = strlen(s);
    char *result = malloc(n * 2 + 1);
    if (!result) return NULL;

    regex_t reg;
    regmatch_t pmatch[2];
    const char *pattern = "([a-z0-9])([A-Z])";
    const char *replacement = "\\1_\\2";

    /* Possible weaknesses found:
     *  Memory leak: result [memleak]
     */
    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) return NULL;

    char tmp[n * 2 + 1];
    snprintf(tmp, sizeof(tmp), "%s", s);

    while (regexec(&reg, tmp, 2, pmatch, 0) == 0) {
        char tmp_result[n * 2 + 1];
        /* Possible weaknesses found:
         *  call to undeclared function 'regexpand'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'regexpand' [-Wimplicit-function-declaration]
         */
        int new_len = regexpand(&reg, tmp, replacement, tmp_result, n * 2 + 1);
        if (new_len < 0) {
            free(result);
            regfree(&reg);
            return NULL;
        }
        strncpy(tmp, tmp_result, new_len);
        tmp[new_len] = '\0';
    }

    strcpy(result, tmp);
    regfree(&reg);
    return result;
}

int main() {
    const char *input = "CamelCaseString";
    char *output = camel_to_snake(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error converting string\n");
    }
    return 0;
}