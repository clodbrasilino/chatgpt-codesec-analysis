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

    size_t max_matches = len + 1;
    regmatch_t *matches = malloc(max_matches * sizeof(regmatch_t));
    if (matches == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_size = len * 2 + 1;
    char *result = malloc(result_size);
    if (result == NULL) {
        free(matches);
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    size_t str_idx = 0;
    int is_first_word = 1;

    while (str_idx < len) {
        int match_ret = regexec(&regex, str + str_idx, 1, matches, 0);
        if (match_ret != 0 || matches[0].rm_so == -1) {
            break;
        }

        if ((size_t)matches[0].rm_so > 0) {
            size_t gap_len = matches[0].rm_so;
            if (result_idx + gap_len >= result_size) {
                result_size = result_idx + gap_len + 1;
                char *temp = realloc(result, result_size);
                if (temp == NULL) {
                    free(result);
                    free(matches);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
            }
            memcpy(result + result_idx, str + str_idx, gap_len);
            result_idx += gap_len;
            str_idx += gap_len;
            is_first_word = 0;
        }

        size_t match_len = matches[0].rm_eo - matches[0].rm_so;
        if (!is_first_word) {
            if (result_idx + 1 >= result_size) {
                result_size = result_idx + match_len + 2;
                char *temp = realloc(result, result_size);
                if (temp == NULL) {
                    free(result);
                    free(matches);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
            }
            result[result_idx++] = ' ';
        }

        if (result_idx + match_len >= result_size) {
            result_size = result_idx + match_len + 1;
            char *temp = realloc(result, result_size);
            if (temp == NULL) {
                free(result);
                free(matches);
                regfree(&regex);
                return NULL;
            }
            result = temp;
        }

        memcpy(result + result_idx, str + str_idx, match_len);
        result_idx += match_len;
        str_idx += matches[0].rm_eo;
        is_first_word = 0;
    }

    if (str_idx < len) {
        size_t remaining = len - str_idx;
        if (result_idx + remaining >= result_size) {
            result_size = result_idx + remaining + 1;
            char *temp = realloc(result, result_size);
            if (temp == NULL) {
                free(result);
                free(matches);
                regfree(&regex);
                return NULL;
            }
            result = temp;
        }
        memcpy(result + result_idx, str + str_idx, remaining);
        result_idx += remaining;
    }

    result[result_idx] = '\0';

    free(matches);
    regfree(&regex);

    char *final_result = realloc(result, result_idx + 1);
    if (final_result == NULL) {
        return result;
    }

    return final_result;
}

int main(void) {
    char *result1 = add_spaces("HelloWorldFromC");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = add_spaces("ThisIsATest");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = add_spaces("NoSpaces");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    char *result4 = add_spaces("already spaced String");
    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }

    char *result5 = add_spaces("");
    if (result5 != NULL) {
        printf("%s\n", result5);
        free(result5);
    }

    return 0;
}