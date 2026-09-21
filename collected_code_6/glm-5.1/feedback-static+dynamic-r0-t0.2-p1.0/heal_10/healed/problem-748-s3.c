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
    if (regcomp(&regex, "([A-Z][a-z]*)", REG_EXTENDED) != 0) {
        return NULL;
    }

    regmatch_t match;

    size_t result_cap = len * 2 + 1;
    char *result = malloc(result_cap);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    size_t str_idx = 0;
    int is_first_word = 1;

    while (str_idx < len) {
        if (regexec(&regex, str + str_idx, 1, &match, 0) != 0 || match.rm_so == -1) {
            break;
        }

        size_t gap_len = match.rm_so;
        if (gap_len > 0) {
            if (result_idx + gap_len >= result_cap) {
                size_t new_cap = result_cap;
                while (result_idx + gap_len >= new_cap) {
                    new_cap *= 2;
                }
                char *temp = realloc(result, new_cap);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
                result_cap = new_cap;
            }
            memcpy(result + result_idx, str + str_idx, gap_len);
            result_idx += gap_len;
            str_idx += gap_len;
            is_first_word = 0;
        }

        size_t match_len = match.rm_eo - match.rm_so;
        if (match_len == 0) {
            str_idx += 1;
            continue;
        }

        if (!is_first_word) {
            if (result_idx + 1 >= result_cap) {
                size_t new_cap = result_cap * 2;
                char *temp = realloc(result, new_cap);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
                result_cap = new_cap;
            }
            result[result_idx++] = ' ';
        }

        if (result_idx + match_len >= result_cap) {
            size_t new_cap = result_cap;
            while (result_idx + match_len >= new_cap) {
                new_cap *= 2;
            }
            char *temp = realloc(result, new_cap);
            if (temp == NULL) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = temp;
            result_cap = new_cap;
        }

        memcpy(result + result_idx, str + str_idx, match_len);
        result_idx += match_len;
        str_idx += match.rm_eo;
        is_first_word = 0;
    }

    if (str_idx < len) {
        size_t remaining = len - str_idx;
        if (result_idx + remaining >= result_cap) {
            size_t new_cap = result_cap;
            while (result_idx + remaining >= new_cap) {
                new_cap *= 2;
            }
            char *temp = realloc(result, new_cap);
            if (temp == NULL) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = temp;
            result_cap = new_cap;
        }
        memcpy(result + result_idx, str + str_idx, remaining);
        result_idx += remaining;
    }

    if (result_idx >= result_cap) {
        char *temp = realloc(result, result_idx + 1);
        if (temp == NULL) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        result = temp;
        result_cap = result_idx + 1;
    }
    result[result_idx] = '\0';

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