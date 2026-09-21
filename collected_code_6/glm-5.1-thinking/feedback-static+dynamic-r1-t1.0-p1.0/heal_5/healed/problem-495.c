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
    size_t to_copy;
    size_t res_idx;
    size_t available;
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
        if (ret != 0) {
            if (ret == REG_NOMATCH) {
                to_copy = (str + len) - ptr;
                available = len - res_idx;
                if (to_copy > available) {
                    to_copy = available;
                }
                memcpy(result + res_idx, ptr, to_copy);
                res_idx += to_copy;
            }
            break;
        }

        to_copy = (size_t)match.rm_so;
        available = len - res_idx;
        if (to_copy > available) {
            to_copy = available;
        }
        memcpy(result + res_idx, ptr, to_copy);
        res_idx += to_copy;

        ptr += match.rm_eo;

        if (match.rm_so == match.rm_eo) {
            if (*ptr != '\0') {
                if (res_idx < len) {
                    result[res_idx++] = *ptr++;
                } else {
                    ptr++;
                }
            } else {
                break;
            }
        }
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