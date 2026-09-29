#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *camel_to_snake(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(s);
    char *result = malloc(n * 2 + 1);
    if (!result) return NULL;

    regex_t reg;
    regmatch_t pmatch[2];
    const char *pattern = "([a-z0-9])([A-Z])";
    /* Possible weaknesses found:
     *  Variable 'replacement' is assigned a value that is never used. [unreadVariable]
     */
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

        /* Possible weaknesses found:
         *  'regex_t' has no member named 'regmatch'
         *  no member named 'regmatch' in 'regex_t'
         */
        int new_len = regerror(reg.regmatch, &reg, tmp_result, n * 2 + 1);
        if (new_len <= 0) {
            free(result);
            free(tmp);
            free(tmp_result);
            regfree(&reg);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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