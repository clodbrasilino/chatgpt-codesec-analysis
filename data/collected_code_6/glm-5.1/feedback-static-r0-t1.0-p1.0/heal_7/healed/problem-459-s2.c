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
    size_t result_len = 0;

    if (input == NULL) {
        return NULL;
    }

    length = strlen(input);
    if (length == SIZE_MAX) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    capacity = length + 1;
    result = malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        
        if (ret == REG_NOMATCH) {
            size_t remaining = strlen(cursor);
            if (remaining > 0) {
                size_t copy_len = remaining;
                if (result_len + copy_len < capacity) {
                    memcpy(result + result_len, cursor, copy_len);
                    result_len += copy_len;
                }
            }
            break;
        }

        if (match.rm_so > 0) {
            size_t copy_len = match.rm_so;
            if (result_len + copy_len < capacity) {
                memcpy(result + result_len, cursor, copy_len);
                result_len += copy_len;
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