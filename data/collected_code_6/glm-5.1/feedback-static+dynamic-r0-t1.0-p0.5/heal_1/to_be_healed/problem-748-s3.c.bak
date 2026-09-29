#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([A-Z][a-z]*)", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_len = len * 2 + 2;
    char *result = malloc(max_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t res_idx = 0;
    const char *ptr = str;
    regmatch_t match[2];

    while (1) {
        ret = regexec(&regex, ptr, 2, match, 0);
        if (ret != 0) {
            break;
        }

        if (match[1].rm_so != -1) {
            size_t prefix_len = match[1].rm_so;
            if (res_idx + prefix_len >= max_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + res_idx, ptr, prefix_len);
            res_idx += prefix_len;

            if (res_idx > 0 && result[res_idx - 1] != ' ') {
                if (res_idx + 1 >= max_len) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result[res_idx++] = ' ';
            }

            size_t word_len = match[1].rm_eo - match[1].rm_so;
            if (res_idx + word_len >= max_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + res_idx, ptr + match[1].rm_so, word_len);
            res_idx += word_len;

            ptr += match[1].rm_eo;
        } else {
            ptr += match[0].rm_eo;
        }

        if (*ptr == '\0') {
            break;
        }
    }

    size_t remaining_len = strlen(ptr);
    if (res_idx + remaining_len >= max_len) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    memcpy(result + res_idx, ptr, remaining_len);
    res_idx += remaining_len;

    result[res_idx] = '\0';

    regfree(&regex);

    char *shrunk = realloc(result, res_idx + 1);
    if (shrunk != NULL) {
        return shrunk;
    }
    return result;
}

int main(void) {
    char *result1 = add_spaces("SplitWordsByCapitalLetters");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = add_spaces("Already Has Spaces");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = add_spaces("NoSpaces");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    char *result4 = add_spaces("");
    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }

    /* Possible weaknesses found:
     *  Assignment 'result5=add_spaces(NULL)', assigned value is 0
     *  Variable 'result5' can be declared as pointer to const [constVariablePointer]
     *  Calling function 'add_spaces' returns 0
     */
    char *result5 = add_spaces(NULL);
    /* Possible weaknesses found:
     *  Condition 'result5==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'result5==NULL' is always true
     */
    if (result5 == NULL) {
        printf("NULL handled\n");
    }

    return 0;
}