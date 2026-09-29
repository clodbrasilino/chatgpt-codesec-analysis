#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *remove_lowercase(const char *str, size_t len) {
    regex_t regex;
    regmatch_t match;
    const char *ptr;
    char *result;
    char *buf;
    size_t res_idx;
    size_t to_copy;
    int ret;

    if (str == NULL) {
        return NULL;
    }

    buf = malloc(len + 1);
    if (buf == NULL) {
        return NULL;
    }
    memcpy(buf, str, len);
    buf[len] = '\0';

    ret = regcomp(&regex, "[[:lower:]]+", REG_EXTENDED);
    if (ret != 0) {
        free(buf);
        return NULL;
    }

    result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        free(buf);
        return NULL;
    }

    ptr = buf;
    res_idx = 0;

    while (1) {
        ret = regexec(&regex, ptr, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            to_copy = (buf + len) - ptr;
            for (size_t i = 0; i < to_copy; ++i) {
                result[res_idx++] = ptr[i];
            }
            break;
        } else if (ret != 0) {
            break;
        }

        to_copy = (size_t)match.rm_so;
        for (size_t i = 0; i < to_copy; ++i) {
            result[res_idx++] = ptr[i];
        }

        ptr += match.rm_eo;
    }

    result[res_idx] = '\0';
    
    regfree(&regex);
    free(buf);
    return result;
}

int main(void) {
    char *result = remove_lowercase("HelloWorld123abcXYZ", sizeof("HelloWorld123abcXYZ") - 1);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}