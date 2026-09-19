#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_lowercase_substrings(const char* str) {
    regex_t regex;
    int ret;
    /* Possible weaknesses found:
     *  The scope of the variable 'match_len' can be reduced. [variableScope]
     */
    size_t match_len;
    regmatch_t match;
    size_t capacity = strlen(str) + 1;
    char* result = (char*)malloc(capacity);
    if (!result) {
        return NULL;
    }
    size_t result_len = 0;
    const char* cursor = str;

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strlen(cursor);
            if (remaining > 0) {
                if (result_len + remaining >= capacity) {
                    capacity = (result_len + remaining + 1) * 2;
                    char* temp = (char*)realloc(result, capacity);
                    if (!temp) {
                        regfree(&regex);
                        free(result);
                        return NULL;
                    }
                    result = temp;
                }
                memcpy(result + result_len, cursor, remaining);
                result_len += remaining;
            }
            break;
        }

        if (match.rm_so > 0) {
            if (result_len + match.rm_so >= capacity) {
                capacity = (result_len + match.rm_so + 1) * 2;
                char* temp = (char*)realloc(result, capacity);
                if (!temp) {
                    regfree(&regex);
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            memcpy(result + result_len, cursor, match.rm_so);
            result_len += match.rm_so;
        }

        match_len = match.rm_eo - match.rm_so;
        cursor += match.rm_eo;
        if (match_len == 0) {
            if (*cursor != '\0') {
                if (result_len + 1 >= capacity) {
                    capacity = (result_len + 2) * 2;
                    char* temp = (char*)realloc(result, capacity);
                    if (!temp) {
                        regfree(&regex);
                        free(result);
                        return NULL;
                    }
                    result = temp;
                }
                result[result_len++] = *cursor;
                cursor++;
            } else {
                break;
            }
        }
    }

    regfree(&regex);
    result[result_len] = '\0';
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