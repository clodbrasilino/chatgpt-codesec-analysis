#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>

char *remove_uppercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);

    if (input_len == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    size_t result_idx = 0;
    const char *ptr = input;
    regmatch_t match;

    while (1) {
        int exec_ret = regexec(&regex, ptr, 1, &match, 0);
        if (exec_ret != 0) {
            break;
        }

        if (match.rm_so > 0) {
            size_t copy_len = (size_t)match.rm_so;
            if (result_idx + copy_len > input_len) {
                break;
            }
            memcpy(result + result_idx, ptr, copy_len);
            result_idx += copy_len;
        }

        ptr += match.rm_eo;
    }

    size_t remaining = input + input_len - ptr;
    if (remaining > 0) {
        if (result_idx + remaining <= input_len) {
            memcpy(result + result_idx, ptr, remaining);
            result_idx += remaining;
        }
    }

    result[result_idx] = '\0';
    regfree(&regex);

    char *shrunk = realloc(result, result_idx + 1);
    if (shrunk != NULL) {
        return shrunk;
    }

    return result;
}

int main(void) {
    const char *str = "abcDEFghiJKLmno";
    char *filtered = remove_uppercase_substrings(str);

    if (filtered != NULL) {
        printf("Original: %s\n", str);
        printf("Filtered: %s\n", filtered);
        free(filtered);
    }

    return 0;
}