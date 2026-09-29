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
    char *res_ptr;
    size_t len;
    size_t to_copy;
    size_t offset;
    int ret;

    if (str == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:lower:]]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    ptr = str;
    res_ptr = result;

    while (1) {
        ret = regexec(&regex, ptr, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            to_copy = (str + len) - ptr;
            offset = (size_t)(res_ptr - result);
            if (offset + to_copy > len) {
                to_copy = len - offset;
            }
            memcpy(res_ptr, ptr, to_copy);
            res_ptr += to_copy;
            break;
        }

        if (match.rm_so > 0) {
            to_copy = (size_t)match.rm_so;
            offset = (size_t)(res_ptr - result);
            if (offset + to_copy > len) {
                to_copy = len - offset;
            }
            memcpy(res_ptr, ptr, to_copy);
            res_ptr += to_copy;
        }

        ptr += match.rm_eo;

        if (match.rm_so == match.rm_eo) {
            if (*ptr != '\0') {
                offset = (size_t)(res_ptr - result);
                if (offset < len) {
                    *res_ptr++ = *ptr++;
                } else {
                    ptr++;
                }
            } else {
                break;
            }
        }
    }

    *res_ptr = '\0';
    
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