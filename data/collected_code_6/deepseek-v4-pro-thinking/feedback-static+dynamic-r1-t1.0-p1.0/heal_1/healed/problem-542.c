#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

void replace_with_colon(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char *errbuf = NULL;
    size_t errbuf_size;
    int ret;

    if (str == NULL) {
        return;
    }

    ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        errbuf_size = regerror(ret, &regex, NULL, 0);
        errbuf = malloc(errbuf_size);
        if (errbuf != NULL) {
            regerror(ret, &regex, errbuf, errbuf_size);
            fprintf(stderr, "regcomp: %s\n", errbuf);
            free(errbuf);
        } else {
            fprintf(stderr, "regcomp: unknown error (malloc failed)\n");
        }
        return;
    }

    char *cur = str;
    while (*cur != '\0') {
        ret = regexec(&regex, cur, 1, match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            errbuf_size = regerror(ret, &regex, NULL, 0);
            errbuf = malloc(errbuf_size);
            if (errbuf != NULL) {
                regerror(ret, &regex, errbuf, errbuf_size);
                fprintf(stderr, "regexec: %s\n", errbuf);
                free(errbuf);
            } else {
                fprintf(stderr, "regexec: unknown error (malloc failed)\n");
            }
            break;
        }
        cur[match[0].rm_so] = ':';
        cur += match[0].rm_so + 1;
    }

    regfree(&regex);
}

int main(void) {
    char text[] = "Hello, world. How are you today?";
    printf("Before: %s\n", text);
    replace_with_colon(text);
    printf("After: %s\n", text);
    return 0;
}