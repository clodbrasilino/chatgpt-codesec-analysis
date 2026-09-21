#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_whitespace_swap(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ _]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *p = str;
    size_t index = 0;
    regmatch_t match;

    while (*p != '\0') {
        ret = regexec(&regex, p, 1, &match, 0);
        if (ret == 0 && match.rm_so == 0) {
            if (*p == ' ') {
                result[index++] = '_';
            } else if (*p == '_') {
                result[index++] = ' ';
            } else {
                result[index++] = *p;
            }
            p += match.rm_eo;
        } else {
            size_t copy_len;
            if (ret == 0) {
                copy_len = match.rm_so;
            } else {
                copy_len = strnlen(p, len - (p - str));
            }
            if (copy_len > 0) {
                size_t remaining = len - index;
                size_t safe_copy_len = copy_len < remaining ? copy_len : remaining;
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(&result[index], p, safe_copy_len);
                index += safe_copy_len;
            }
            p += copy_len;
        }
    }

    result[index] = '\0';
    regfree(&regex);

    char *shrunk = realloc(result, index + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    char *result1 = replace_whitespace_swap("hello world_this_is_a_test");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = replace_whitespace_swap("no_spaces_or_underscores");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    /* Possible weaknesses found:
     *  Calling function 'replace_whitespace_swap' returns 0
     *  Assignment 'result3=replace_whitespace_swap(NULL)', assigned value is 0
     */
    const char *result3 = replace_whitespace_swap(NULL);
    /* Possible weaknesses found:
     *  Condition 'result3==NULL' is always true
     *  Condition 'result3==NULL' is always true [knownConditionTrueFalse]
     */
    if (result3 == NULL) {
        printf("Handled NULL input correctly\n");
    }

    return 0;
}