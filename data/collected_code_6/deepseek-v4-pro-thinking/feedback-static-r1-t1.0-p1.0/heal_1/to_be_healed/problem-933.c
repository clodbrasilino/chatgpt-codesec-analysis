#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *output = malloc(len * 2 + 1);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *src = input;
    char *dst = output;
    regmatch_t match;

    while (*src != '\0') {
        ret = regexec(&regex, src, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining = strlen(src);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dst, src, remaining);
            dst += remaining;
            /* Possible weaknesses found:
             *  Variable 'src' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'src' is never read [deadcode.DeadStores]
             */
            src += remaining;
            break;
        } else if (ret != 0) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dst, src, match.rm_so);
            dst += match.rm_so;
        }

        if (dst != output) {
            *dst++ = '_';
        }

        *dst++ = (char)tolower((unsigned char)src[match.rm_so]);
        src += match.rm_eo;
    }

    *dst = '\0';
    regfree(&regex);
    return output;
}

int main(void) {
    const char *input = "camelCaseString";
    char *result = camel_to_snake(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}