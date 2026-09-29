#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *camel_to_snake(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char tmp[n * 2 + 1];
    snprintf(tmp, sizeof(tmp), "%s", s);

    while (regexec(&reg, tmp, 2, pmatch, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char tmp_result[n * 2 + 1];
        /* Possible weaknesses found:
         *  implicit declaration of function 'regexpand' [-Wimplicit-function-declaration]
         *  call to undeclared function 'regexpand'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        int new_len = regexpand(&reg, tmp, replacement, tmp_result, n * 2 + 1);
        if (new_len < 0) {
            free(result);
            regfree(&reg);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(tmp, tmp_result, new_len);
        tmp[new_len] = '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
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