#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_non_alnum(char *str) {
    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t total_len = strlen(str);
    regex_t regex;
    int ret = regcomp(&regex, "[^[:alnum:]]", REG_EXTENDED);
    if (ret != 0) {
        size_t errbuf_size = regerror(ret, &regex, NULL, 0);
        char *errbuf = malloc(errbuf_size);
        if (errbuf != NULL) {
            regerror(ret, &regex, errbuf, errbuf_size);
            fprintf(stderr, "regcomp failed: %s\n", errbuf);
            free(errbuf);
        } else {
            fprintf(stderr, "regcomp failed\n");
        }
        return -1;
    }

    char *src = str;
    char *dst = str;
    regmatch_t match;

    while (*src) {
        ret = regexec(&regex, src, 1, &match, 0);
        if (ret == 0) {
            if (match.rm_so > 0) {
                size_t len = (size_t)match.rm_so;
                memmove(dst, src, len);
                dst += len;
            }
            src += match.rm_eo;
        } else if (ret == REG_NOMATCH) {
            size_t len = total_len - (size_t)(src - str);
            memmove(dst, src, len + 1);
            dst += len;
            break;
        } else {
            size_t errbuf_size = regerror(ret, &regex, NULL, 0);
            char *errbuf = malloc(errbuf_size);
            if (errbuf != NULL) {
                regerror(ret, &regex, errbuf, errbuf_size);
                fprintf(stderr, "regexec failed: %s\n", errbuf);
                free(errbuf);
            } else {
                fprintf(stderr, "regexec failed\n");
            }
            regfree(&regex);
            return -1;
        }
    }

    *dst = '\0';
    regfree(&regex);
    return 0;
}

int main(void) {
    char text[] = "Hello, World! 123";

    if (remove_non_alnum(text) != 0) {
        return EXIT_FAILURE;
    }

    printf("%s\n", text);
    return EXIT_SUCCESS;
}