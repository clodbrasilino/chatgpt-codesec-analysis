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
    const char *replacement = "\\1_\\2";

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        free(result);
        return NULL;
    }

    char *tmp = malloc(n * 2 + 1);
    if (!tmp) {
        free(result);
        return NULL;
    }
    snprintf(tmp, n * 2 + 1, "%s", s);

    while (regexec(&reg, tmp, 2, pmatch, 0) == 0) {
        char *tmp_result = malloc(n * 2 + 1);
        if (!tmp_result) {
            free(tmp);
            free(result);
            regfree(&reg);
            return NULL;
        }
        /* Possible weaknesses found:
         *  call to undeclared function 'regsub'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'regsub' [-Wimplicit-function-declaration]
         */
        regsub(&reg, tmp, 2, pmatch, replacement, tmp_result, n * 2 + 1);
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(tmp, tmp_result, n * 2 + 1);
        tmp[n * 2] = '\0';
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