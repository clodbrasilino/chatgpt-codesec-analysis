#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_lowercase_substrings(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_matches = strnlen(str, SIZE_MAX) / 2 + 1;
    regmatch_t* matches = malloc(max_matches * sizeof(regmatch_t));
    if (matches == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_size = strnlen(str, SIZE_MAX) + 1;
    char* result = malloc(result_size);
    if (result == NULL) {
        free(matches);
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    const char* current = str;
    const char* str_end = str + strnlen(str, SIZE_MAX);

    while (1) {
        ret = regexec(&regex, current, 1, matches, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = str_end - current;
            if (result_idx + remaining < result_size) {
                memcpy(result + result_idx, current, remaining);
            }
            result_idx += remaining;
            break;
        }

        if (ret != 0) {
            free(result);
            free(matches);
            regfree(&regex);
            return NULL;
        }

        size_t prefix_len = matches[0].rm_so;
        if (result_idx + prefix_len < result_size) {
            memcpy(result + result_idx, current, prefix_len);
        }
        result_idx += prefix_len;

        current += matches[0].rm_eo;
    }

    if (result_idx < result_size) {
        result[result_idx] = '\0';
    }

    char* final_result = realloc(result, result_idx + 1);
    if (final_result == NULL) {
        free(result);
        free(matches);
        regfree(&regex);
        return NULL;
    }

    free(matches);
    regfree(&regex);

    return final_result;
}

int main() {
    const char* input = "Hello World abc DEF 123 xyz";
    char* output = remove_lowercase_substrings(input);

    if (output != NULL) {
        printf("Original: %s\n", input);
        printf("Modified: %s\n", output);
        free(output);
    }

    return 0;
}