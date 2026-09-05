#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>

char *remove_uppercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strlen(input);
    char *result = malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
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
            memcpy(result + result_idx, ptr, match.rm_so);
            result_idx += match.rm_so;
        }

        ptr += match.rm_eo;
    }

    size_t remaining = strlen(ptr);
    if (remaining > 0) {
        memcpy(result + result_idx, ptr, remaining);
        result_idx += remaining;
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