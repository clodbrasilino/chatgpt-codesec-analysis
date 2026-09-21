#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool has_unique_chars(const char *str)
{
    bool seen[UCHAR_MAX + 1] = {false};
    size_t i;
    size_t len;

    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len > (size_t)(UCHAR_MAX + 1)) {
        return false;
    }

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return false;
        }
        seen[c] = true;
    }

    return true;
}

int main(void)
{
    const char *tests[] = {
        "abcdefg",
        "hello",
        "",
        "aA",
        "unique"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        printf("\"%s\": %s\n", tests[i],
               has_unique_chars(tests[i]) ? "unique" : "not unique");
    }

    return 0;
}