#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_concatenation(const char *str, const char *pattern)
{
    size_t str_len;
    size_t pat_len;
    size_t i;

    if (str == NULL || pattern == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    str_len = strlen(str);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    pat_len = strlen(pattern);

    if (pat_len == 0 || str_len == 0) {
        return false;
    }

    if (str_len % pat_len != 0) {
        return false;
    }

    for (i = 0; i < str_len; i++) {
        if (str[i] != pattern[i % pat_len]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const char *tests[][2] = {
        {"abcabcabc", "abc"},
        {"abcabcab", "abc"},
        {"aaaa", "a"},
        {"hello", "hello"},
        {"hellohello", "hello"},
        {"", "abc"},
        {"abc", ""}
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        if (is_concatenation(tests[i][0], tests[i][1])) {
            if (printf("\"%s\" is a concatenation of \"%s\"\n",
                       tests[i][0], tests[i][1]) < 0) {
                return 1;
            }
        } else {
            if (printf("\"%s\" is NOT a concatenation of \"%s\"\n",
                       tests[i][0], tests[i][1]) < 0) {
                return 1;
            }
        }
    }

    return 0;
}