#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_INPUT_LEN 4096

bool can_rearrange_no_adjacent(const char *str)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t len;
    size_t max_count = 0;
    size_t i;

    if (str == NULL) {
        return false;
    }

    len = strnlen(str, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN && str[MAX_INPUT_LEN - 1] != '\0') {
        return false;
    }

    if (len == 0) {
        return true;
    }

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
        }
    }

    return max_count <= (len + 1) / 2;
}

int main(void)
{
    const char *tests[] = {
        "aab",
        "aaab",
        "aa",
        "a",
        "",
        "abcdef",
        "aabbcc",
        "aaaabc"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        bool result = can_rearrange_no_adjacent(tests[i]);
        if (printf("\"%s\": %s\n", tests[i], result ? "yes" : "no") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}