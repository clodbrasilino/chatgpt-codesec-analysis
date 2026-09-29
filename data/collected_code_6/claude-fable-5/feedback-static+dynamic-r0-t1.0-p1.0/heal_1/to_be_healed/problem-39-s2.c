#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool can_rearrange_no_adjacent(const char *str)
{
    size_t counts[256] = {0};
    size_t len;
    size_t max_count = 0;
    size_t i;

    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
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
        "aaabc"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        if (printf("\"%s\": %s\n", tests[i],
                   can_rearrange_no_adjacent(tests[i]) ? "yes" : "no") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}