#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool has_unique_chars(const char *str)
{
    bool seen[UCHAR_MAX + 1] = {false};
    size_t i;

    if (str == NULL) {
        return false;
    }

    for (i = 0; str[i] != '\0'; i++) {
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
        "abcdefghijklmnopqrstuvwxyz",
        "abcda"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        printf("\"%s\" -> %s\n",
               tests[i],
               has_unique_chars(tests[i]) ? "unique" : "not unique");
    }

    return 0;
}