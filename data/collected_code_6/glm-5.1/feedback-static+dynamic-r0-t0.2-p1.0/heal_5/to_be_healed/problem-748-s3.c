#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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

    size_t max_matches = len + 1;
    regmatch_t *matches = malloc(max_matches * sizeof(regmatch_t));
    if (matches == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_cap = len * 2 + 1;
    char *result = malloc(result_cap);
    if (result == NULL) {
        free(matches);
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    size_t str_idx = 0;
    int is_first_word = 1;

    while (str_idx < len) {
        if (regexec(&regex, str + str_idx, 1, matches, 0) != 0 || matches[0].rm_so == -1) {
            break;
        }

        if ((size_t)matches[0].rm_so > 0) {
            size_t gap_len = matches[0].rm_so;
            while (result_idx + gap_len >= result_cap) {
                result_cap *= 2;
                char *temp = realloc(result, result_cap);
                if (temp == NULL) {
                    free(result);
                    free(matches);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_idx, str + str_idx, gap_len);
            result_idx += gap_len;
            str_idx += gap_len;
            is_first_word = 0;
        }

        size_t match_len = matches[0].rm_eo - matches[0].rm_so;
        if (!is_first_word) {
            while (result_idx + 1 >= result_cap) {
                result_cap *= 2;
                char *temp = realloc(result, result_cap);
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

        while (result_idx + match_len >= result_cap) {
            result_cap *= 2;
            char *temp = realloc(result, result_cap);
            if (temp == NULL) {
                free(result);
                free(matches);
                regfree(&regex);
                return NULL;
            }
            result = temp;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_idx, str + str_idx, match_len);
        result_idx += match_len;
        str_idx += matches[0].rm_eo;
        is_first_word = 0;
    }

    if (str_idx < len) {
        size_t remaining = len - str_idx;
        while (result_idx + remaining >= result_cap) {
            result_cap *= 2;
            char *temp = realloc(result, result_cap);
            if (temp == NULL) {
                free(result);
                free(matches);
                regfree(&regex);
                return NULL;
            }
            result = temp;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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