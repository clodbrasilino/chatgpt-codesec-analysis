#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alphanumeric(const char *input)
{
    regex_t regex;
    char *result;
    size_t len;
    size_t pos = 0;
    size_t out = 0;

    if (input == NULL)
        return NULL;

    if (regcomp(&regex, "[^[:alnum:]]", REG_EXTENDED) != 0)
        return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (pos < len) {
        regmatch_t match;
        int ret = regexec(&regex, input + pos, 1, &match, 0);

        if (ret == 0) {
            if (match.rm_so > 0) {
                size_t n = (size_t)match.rm_so;
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + out, input + pos, n);
                out += n;
            }
            if (match.rm_eo <= match.rm_so) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            pos += (size_t)match.rm_eo;
        } else if (ret == REG_NOMATCH) {
            size_t n = len - pos;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + out, input + pos, n);
            out += n;
            pos = len;
        } else {
            regfree(&regex);
            free(result);
            return NULL;
        }
    }

    result[out] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    char *cleaned = remove_non_alphanumeric("Hello, World! 123");
    if (cleaned != NULL) {
        puts(cleaned);
        free(cleaned);
    }
    return 0;
}