#define _POSIX_C_SOURCE 200809L
#include <regex.h>
#include <string.h>
#include <stdio.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    if (regcomp(&regex, "[a-z]+", REG_EXTENDED) != 0) return;

    char *src = str, *dst = str;
    char *end = str + strlen(str);
    regmatch_t match;

    while (regexec(&regex, src, 1, &match, 0) == 0) {
        size_t unmatched = match.rm_so;
        if (unmatched > 0) {
            memmove(dst, src, unmatched);
            dst += unmatched;
        }
        src += match.rm_eo;
        if (match.rm_eo == 0) {
            if (*src) {
                *dst++ = *src++;
            } else {
                break;
            }
        }
    }
    size_t rest = end - src;
    memmove(dst, src, rest + 1);
    regfree(&regex);
}

int main(void) {
    char str[] = "HelloWorld abc DEF123ghi xyz";
    remove_lowercase_substrings(str);
    printf("%s\n", str);
    return 0;
}