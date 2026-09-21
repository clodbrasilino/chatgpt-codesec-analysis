#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_lowercase_substrings(const char* str) {
    if (!str) {
        return NULL;
    }

    regex_t regex;
    int ret;
    regmatch_t match;
    size_t capacity = strnlen(str, SIZE_MAX) + 1;
    const char* cursor = str;

    char* result = (char*)malloc(capacity);
    if (!result) {
        return NULL;
    }
    size_t result_len = 0;

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(cursor, capacity - (cursor - str));
            if (remaining > 0) {
                if (result_len + remaining + 1 > capacity) {
                    capacity = (result_len + remaining + 1) * 2;
                    char* temp = (char*)realloc(result, capacity);
                    if (!temp) {
                        regfree(&regex);
                        free(result);
                        return NULL;
                    }
                    result = temp;
                }
                if (result_len + remaining <= capacity) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + result_len, cursor, remaining);
                }
                result_len += remaining;
            }
            break;
        }

        if (match.rm_so > 0) {
            if (result_len + match.rm_so + 1 > capacity) {
                capacity = (result_len + match.rm_so + 1) * 2;
                char* temp = (char*)realloc(result, capacity);
                if (!temp) {
                    regfree(&regex);
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            if (result_len + match.rm_so <= capacity) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, cursor, match.rm_so);
            }
            result_len += match.rm_so;
        }

        size_t match_len = match.rm_eo - match.rm_so;
        cursor += match.rm_eo;
        if (match_len == 0) {
            if (*cursor != '\0') {
                if (result_len + 2 > capacity) {
                    capacity = (result_len + 2) * 2;
                    char* temp = (char*)realloc(result, capacity);
                    if (!temp) {
                        regfree(&regex);
                        free(result);
                        return NULL;
                    }
                    result = temp;
                }
                if (result_len + 1 <= capacity) {
                    result[result_len] = *cursor;
                    result_len++;
                }
                cursor++;
            } else {
                break;
            }
        }
    }

    regfree(&regex);
    if (result_len < capacity) {
        result[result_len] = '\0';
    } else {
        char* temp = (char*)realloc(result, result_len + 1);
        if (temp) {
            result = temp;
            result[result_len] = '\0';
        } else {
            free(result);
            return NULL;
        }
    }
    char* final_result = (char*)realloc(result, result_len + 1);
    return final_result ? final_result : result;
}

int main(void) {
    char* res1 = remove_lowercase_substrings("HelloWorld123abcDEF");
    if (res1) {
        printf("%s\n", res1);
        free(res1);
    }

    char* res2 = remove_lowercase_substrings("TESTlowerCASE");
    if (res2) {
        printf("%s\n", res2);
        free(res2);
    }

    char* res3 = remove_lowercase_substrings("123456");
    if (res3) {
        printf("%s\n", res3);
        free(res3);
    }

    char* res4 = remove_lowercase_substrings("alllowercase");
    if (res4) {
        printf("%s\n", res4);
        free(res4);
    }

    return 0;
}