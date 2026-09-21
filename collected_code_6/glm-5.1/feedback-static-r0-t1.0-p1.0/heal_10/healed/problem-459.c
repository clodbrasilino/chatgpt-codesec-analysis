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
    size_t result_idx = 0;
    size_t copy_len;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    length = strnlen(input, SIZE_MAX);
    if (length == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    capacity = length + 1;
    result = (char *)malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            copy_len = (input + length) - cursor;
            if (copy_len > 0) {
                if (result_idx + copy_len + 1 > capacity) {
                    capacity = result_idx + copy_len + 1;
                    char *temp = (char *)realloc(result, capacity);
                    if (temp == NULL) {
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                }
                if (result_idx + copy_len <= capacity) {
                    memcpy(result + result_idx, cursor, copy_len);
                } else {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
            }
            result_idx += copy_len;
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        copy_len = match.rm_so;
        if (copy_len > 0) {
            if (result_idx + copy_len + 1 > capacity) {
                capacity = (result_idx + copy_len) * 2 + 1;
                char *temp = (char *)realloc(result, capacity);
                if (temp == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = temp;
            }
            if (result_idx + copy_len <= capacity) {
                memcpy(result + result_idx, cursor, copy_len);
            } else {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result_idx += copy_len;
        }

        cursor += match.rm_eo;
    }

    result[result_idx] = '\0';
    
    char *shrunk = (char *)realloc(result, result_idx + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    char *result = remove_uppercase_substrings("HelloWORLDEveryoneTHISIsATest");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = remove_uppercase_substrings("NO_LOWER_CASE_HERE");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    
    result = remove_uppercase_substrings("only_lower_case_here");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}