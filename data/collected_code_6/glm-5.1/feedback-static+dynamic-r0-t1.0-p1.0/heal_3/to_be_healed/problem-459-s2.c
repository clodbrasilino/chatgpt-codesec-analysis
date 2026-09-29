#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_uppercase_substrings(const char *input) {
    regex_t regex;
    int ret;
    regmatch_t match;
    size_t capacity;
    size_t length;
    char *result;
    const char *cursor;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    length = 0;
    while (input[length] != '\0') {
        length++;
    }
    capacity = length + 1;
    result = malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    size_t result_len = 0;

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        
        if (ret == REG_NOMATCH) {
            size_t remaining = 0;
            while (cursor[remaining] != '\0') {
                remaining++;
            }
            if (remaining > 0) {
                if (result_len + remaining <= capacity - 1) {
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
            if (result_len + (size_t)match.rm_so <= capacity - 1) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, cursor, match.rm_so);
            }
            result_len += match.rm_so;
        }

        cursor += match.rm_eo;
    }

    result[result_len] = '\0';

    char *final_result = realloc(result, result_len + 1);
    if (final_result == NULL) {
        regfree(&regex);
        free(result);
        return NULL;
    }

    regfree(&regex);
    return final_result;
}

int main(void) {
    char *result = remove_uppercase_substrings("abcHELLOdefWORLDghi");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_uppercase_substrings("ALLCAPS");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_uppercase_substrings("nocaps");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_uppercase_substrings("MixedCASEstring");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}