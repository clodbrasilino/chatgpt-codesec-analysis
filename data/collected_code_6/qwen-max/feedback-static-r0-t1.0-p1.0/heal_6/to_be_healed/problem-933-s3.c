#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *camel_to_snake(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(s);
    char *result = malloc((n * 2 + 1) * sizeof(char));
    if (!result) return NULL;

    regex_t reg;
    regmatch_t pmatch[2];
    const char *pattern = "([a-z0-9])([A-Z])";

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

    size_t new_len = n;
    while (regexec(&reg, tmp, 2, pmatch, 0) == 0) {
        size_t offset = pmatch[0].rm_so;
        memmove(&tmp[offset + 1], &tmp[offset + 1], new_len - offset - 1);
        tmp[offset] = '_';
        tmp[new_len++] = '\0';
    }

    snprintf(result, new_len * 2 + 1, "%s", tmp);
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