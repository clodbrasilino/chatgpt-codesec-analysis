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
    size_t available = input_len;

    while (available > 0) {
        int exec_ret = regexec(&regex, ptr, 1, &match, 0);
        if (exec_ret != 0) {
            break;
        }

        if ((size_t)match.rm_so >= available) {
            break;
        }

        if (match.rm_so > 0) {
            size_t copy_len = (size_t)match.rm_so;
            if (result_idx + copy_len > input_len) {
                break;
            }
            if (copy_len <= input_len - result_idx) {
                memcpy(result + result_idx, ptr, copy_len);
            }
            result_idx += copy_len;
            available -= copy_len;
        }

        if ((size_t)match.rm_eo > available) {
            break;
        }
        ptr += match.rm_eo;
        available -= (size_t)match.rm_eo;
    }

    if (available > 0 && ptr >= input && ptr < input + input_len + 1) {
        size_t remaining = input_len - (size_t)(ptr - input);
        if (remaining <= available && result_idx + remaining <= input_len) {
            if (remaining <= input_len - result_idx) {
                memcpy(result + result_idx, ptr, remaining);
            }
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