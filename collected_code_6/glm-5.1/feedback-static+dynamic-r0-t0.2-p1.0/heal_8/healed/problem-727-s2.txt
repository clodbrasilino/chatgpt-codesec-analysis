#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);
    size_t result_size = input_len + 1;
    char *result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    size_t result_idx = 0;
    size_t search_start = 0;
    regmatch_t match;

    while (search_start < input_len) {
        int exec_ret = regexec(&regex, input + search_start, 1, &match, 0);
        if (exec_ret == REG_NOMATCH) {
            size_t remaining_len = input_len - search_start;
            if (remaining_len > 0) {
                if (result_idx + remaining_len <= result_size) {
                    memcpy(result + result_idx, input + search_start, remaining_len);
                }
                result_idx += remaining_len;
            }
            break;
        } else if (exec_ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so == -1) {
            break;
        }

        size_t match_start = search_start + match.rm_so;
        size_t match_end = search_start + match.rm_eo;

        size_t copy_len = match_start - search_start;
        if (copy_len > 0) {
            if (result_idx + copy_len <= result_size) {
                memcpy(result + result_idx, input + search_start, copy_len);
            }
            result_idx += copy_len;
        }

        search_start = match_end;
    }

    if (result_idx < result_size) {
        result[result_idx] = '\0';
    } else {
        result[result_size - 1] = '\0';
    }

    char *trimmed_result = realloc(result, result_idx + 1);
    if (trimmed_result != NULL) {
        result = trimmed_result;
    }

    regfree(&regex);

    return result;
}

int main(void) {
    char *result1 = remove_non_alnum("Hello, World! 123");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = remove_non_alnum("___test___");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = remove_non_alnum("");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    char *result4 = remove_non_alnum(NULL);
    (void)result4;

    return 0;
}