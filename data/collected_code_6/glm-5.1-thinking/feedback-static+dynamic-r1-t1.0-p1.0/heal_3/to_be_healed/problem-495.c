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
    size_t avail;
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
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
            offset = (size_t)(res_ptr - result);
            if (offset <= len) {
                avail = (len + 1) - offset;
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                to_copy = strlen(ptr);
                if (to_copy >= avail) {
                    to_copy = avail - 1;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(res_ptr, ptr, to_copy);
                res_ptr += to_copy;
            }
            break;
        }

        if (match.rm_so > 0) {
            offset = (size_t)(res_ptr - result);
            if (offset <= len) {
                avail = (len + 1) - offset;
                to_copy = (size_t)match.rm_so;
                if (to_copy >= avail) {
                    to_copy = avail - 1;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(res_ptr, ptr, to_copy);
                res_ptr += to_copy;
            }
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

    offset = (size_t)(res_ptr - result);
    if (offset > len) {
        res_ptr = result + len;
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