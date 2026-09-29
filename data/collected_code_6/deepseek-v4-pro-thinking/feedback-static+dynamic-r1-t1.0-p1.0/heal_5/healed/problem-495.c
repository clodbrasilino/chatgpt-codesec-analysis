#define _POSIX_C_SOURCE 200809L
#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void remove_lowercase_substrings(char *str) {
    if (str == NULL) return;

    regex_t regex;
    if (regcomp(&regex, "[a-z]+", REG_EXTENDED) != 0) return;

    size_t len = strnlen(str, SIZE_MAX);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return;
    }

    const char *src = str;
    char *dst = result;
    size_t space = len;
    regmatch_t match;

    while (regexec(&regex, src, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo < 0) break;
        if (match.rm_so > match.rm_eo) break;

        size_t pre = (size_t)match.rm_so;
        size_t mlen = (size_t)(match.rm_eo - match.rm_so);

        if (pre > space) break;

        if (pre > 0) {
            memcpy(dst, src, pre);
            dst += pre;
            space -= pre;
            src += pre;
        }

        src += mlen;

        if (mlen == 0) {
            if (*src == '\0' || space == 0) break;
            *dst++ = *src++;
            space--;
        }
    }

    size_t rest = strnlen(src, space);
    if (rest > 0) {
        memcpy(dst, src, rest);
        dst += rest;
        space -= rest;
    }

    *dst = '\0';

    size_t new_len = (size_t)(dst - result);
    memmove(str, result, new_len);
    str[new_len] = '\0';

    free(result);
    regfree(&regex);
}

int main(void) {
    char str[] = "HelloWorld abc DEF123ghi xyz";
    remove_lowercase_substrings(str);
    printf("%s\n", str);
    return 0;
}