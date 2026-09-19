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

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        free(result);
        return NULL;
    }

    char tmp[n * 2 + 1];
    snprintf(tmp, sizeof(tmp), "%s", s);

    while (regexec(&reg, tmp, 2, pmatch, 0) == 0) {
        size_t new_len;
        char tmp_result[n * 2 + 1];
        if (regsub(&reg, 2, pmatch, replacement, &new_len, tmp_result, sizeof(tmp_result)) != 0) {
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