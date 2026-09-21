#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *remove_lowercase(const char *str) {
    regex_t regex;
    regmatch_t match;
    const char *ptr;
    char *result;
    size_t len;
    size_t res_idx;
    size_t to_copy;
    int ret;

    if (str == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:lower:]]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    len = strlen(str);
    result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    ptr = str;
    res_idx = 0;

    while (1) {
        ret = regexec(&regex, ptr, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            to_copy = (str + len) - ptr;
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
    return result;
}

int main(void) {
    char *result = remove_lowercase("HelloWorld123abcXYZ");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}