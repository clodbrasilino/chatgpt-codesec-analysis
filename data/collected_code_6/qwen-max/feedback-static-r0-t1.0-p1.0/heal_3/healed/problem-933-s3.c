#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *camel_to_snake(const char *s) {
    size_t n = strlen(s);
    char *result = malloc(n * 2 + 1);
    if (!result) return NULL;

    regex_t reg;
    regmatch_t pmatch[2];
    const char *pattern = "([a-z0-9])([A-Z])";
    const char *replacement = "\\1_\\2";

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        free(result);
        return NULL;
    }

    char *tmp = strdup(s);
    if (!tmp) {
        free(result);
        regfree(&reg);
        return NULL;
    }

    while (regexec(&reg, tmp, 2, pmatch, 0) == 0) {
        char *tmp_result = malloc(n * 2 + 1);
        if (!tmp_result) {
            free(result);
            free(tmp);
            regfree(&reg);
            return NULL;
        }

        int new_len = regerror(reg.regmatch, &reg, tmp_result, n * 2 + 1);
        if (new_len <= 0) {
            free(result);
            free(tmp);
            free(tmp_result);
            regfree(&reg);
            return NULL;
        }

        memcpy(tmp, tmp_result, new_len);
        tmp[new_len] = '\0';
        free(tmp_result);
    }

    snprintf(result, n * 2 + 1, "%s", tmp);
    free(tmp);
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