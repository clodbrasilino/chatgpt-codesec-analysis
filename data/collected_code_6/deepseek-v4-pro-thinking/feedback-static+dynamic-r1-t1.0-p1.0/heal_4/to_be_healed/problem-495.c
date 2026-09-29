#define _POSIX_C_SOURCE 200809L
#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    if (str == NULL) return;

    regex_t regex;
    if (regcomp(&regex, "[a-z]+", REG_EXTENDED) != 0) return;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return;
    }

    char *src = str;
    char *dst = result;
    regmatch_t match;
    size_t remaining_dst = len;
    size_t remaining_src = len;

    while (regexec(&regex, src, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo < 0 ||
            (size_t)match.rm_so > remaining_src ||
            (size_t)match.rm_eo > remaining_src) {
            break;
        }

        size_t unmatched = (size_t)match.rm_so;
        if (unmatched > remaining_dst) break;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dst, src, unmatched);
        dst += unmatched;
        remaining_dst -= unmatched;
        src += match.rm_eo;
        remaining_src -= match.rm_eo;

        if (match.rm_eo == 0) {
            if (remaining_src == 0) break;
            if (remaining_dst == 0) break;
            *dst++ = *src++;
            remaining_dst--;
            remaining_src--;
        }
    }

    size_t rest_len = remaining_src;
    if (rest_len > remaining_dst) rest_len = remaining_dst;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst, src, rest_len);
    dst += rest_len;
    *dst = '\0';

    size_t res_len = dst - result;
    memmove(str, result, res_len);
    str[res_len] = '\0';

    free(result);
    regfree(&regex);
}

int main(void) {
    char str[] = "HelloWorld abc DEF123ghi xyz";
    remove_lowercase_substrings(str);
    printf("%s\n", str);
    return 0;
}