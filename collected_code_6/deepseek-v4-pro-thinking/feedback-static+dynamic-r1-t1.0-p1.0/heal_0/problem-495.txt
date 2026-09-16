#define _POSIX_C_SOURCE 200809L
#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    int ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return;
    }

    char *src = str;
    char *dst = result;
    regmatch_t match;

    while (regexec(&regex, src, 1, &match, 0) == 0) {
        size_t unmatched = match.rm_so;
        memcpy(dst, src, unmatched);
        dst += unmatched;
        src += match.rm_eo;

        if (match.rm_eo == 0) {
            if (*src != '\0') {
                *dst++ = *src++;
            } else {
                break;
            }
        }
    }

    strcpy(dst, src);
    strcpy(str, result);

    free(result);
    regfree(&regex);
}

int main(void) {
    char str[] = "HelloWorld abc DEF123ghi xyz";
    remove_lowercase_substrings(str);
    printf("%s\n", str);
    return 0;
}