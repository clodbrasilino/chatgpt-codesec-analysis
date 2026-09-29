#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LEN 4096

bool is_concatenation(const char *str, const char *pattern)
{
    size_t str_len;
    size_t pat_len;
    size_t i;

    if (str == NULL || pattern == NULL) {
        return false;
    }

    str_len = strnlen(str, MAX_INPUT_LEN);
    if (str_len == MAX_INPUT_LEN) {
        return false;
    }

    pat_len = strnlen(pattern, MAX_INPUT_LEN);
    if (pat_len == MAX_INPUT_LEN) {
        return false;
    }

    if (pat_len == 0 || str_len == 0) {
        return false;
    }

    if (str_len % pat_len != 0) {
        return false;
    }

    for (i = 0; i < str_len; i += pat_len) {
        if (strncmp(str + i, pattern, pat_len) != 0) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *test_str1 = "abcabcabc";
    const char *test_str2 = "abcabcab";
    const char *pattern = "abc";

    if (is_concatenation(test_str1, pattern)) {
        if (printf("\"%s\" is a concatenation of \"%s\"\n", test_str1, pattern) < 0) {
            return 1;
        }
    } else {
        if (printf("\"%s\" is not a concatenation of \"%s\"\n", test_str1, pattern) < 0) {
            return 1;
        }
    }

    if (is_concatenation(test_str2, pattern)) {
        if (printf("\"%s\" is a concatenation of \"%s\"\n", test_str2, pattern) < 0) {
            return 1;
        }
    } else {
        if (printf("\"%s\" is not a concatenation of \"%s\"\n", test_str2, pattern) < 0) {
            return 1;
        }
    }

    return 0;
}