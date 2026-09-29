#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase(const char *str) {
    regex_t regex;
    regmatch_t match;
    const char *ptr;
    char *result;
    char *res_ptr;
    size_t len;
    size_t res_len;
    size_t copy_len;
    int ret;

    if (str == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:lower:]]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    len = strlen(str);
    result = (char *)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    ptr = str;
    res_ptr = result;
    res_len = 0;

    while (1) {
        ret = regexec(&regex, ptr, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            snprintf(res_ptr, len + 1 - res_len, "%s", ptr);
            break;
        }

        if (match.rm_so > 0) {
            copy_len = match.rm_so;
            if (res_len + copy_len > len) {
                copy_len = len - res_len;
            }
            memcpy(res_ptr, ptr, copy_len);
            res_ptr += copy_len;
            res_len += copy_len;
        }

        ptr += match.rm_eo;

        if (match.rm_so == match.rm_eo) {
            if (*ptr != '\0') {
                if (res_len + 1 <= len) {
                    *res_ptr++ = *ptr++;
                    res_len++;
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