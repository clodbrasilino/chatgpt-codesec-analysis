#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_uppercase_substrings(const char *input) {
    regex_t regex;
    int ret;
    regmatch_t match;
    size_t length;
    char *result;
    const char *cursor;
    size_t max_copy;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    length = strnlen(input, SIZE_MAX);
    
    result = malloc(length + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    size_t result_len = 0;

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        
        if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(cursor, length - (cursor - input));
            max_copy = (length + 1) - result_len;
            size_t to_copy = remaining < max_copy ? remaining : max_copy;
            if (to_copy > 0) {
                if (result_len + to_copy <= length + 1) {
                    memcpy(result + result_len, cursor, to_copy);
                    result_len += to_copy;
                }
            }
            break;
        }

        if (match.rm_so > 0) {
            max_copy = (length + 1) - result_len;
            size_t to_copy = (size_t)match.rm_so < max_copy ? (size_t)match.rm_so : max_copy;
            if (to_copy > 0) {
                if (result_len + to_copy <= length + 1) {
                    memcpy(result + result_len, cursor, to_copy);
                    result_len += to_copy;
                }
            }
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