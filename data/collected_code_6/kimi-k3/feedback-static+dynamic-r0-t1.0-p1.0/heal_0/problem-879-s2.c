#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_a_anything_b(const char *str)
{
    regex_t regex;
    int result;

    if (str == NULL) {
        return 0;
    }

    result = regcomp(&regex, "a.*b$", REG_EXTENDED);
    if (result != 0) {
        return 0;
    }

    result = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return (result == 0) ? 1 : 0;
}

int main(void)
{
    const char *test_strings[] = {
        "ab",
        "axyzb",
        "a123b",
        "ba",
        "acb",
        "xyz",
        "a",
        "b"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        if (match_a_anything_b(test_strings[i])) {
            printf("\"%s\" matches\n", test_strings[i]);
        } else {
            printf("\"%s\" does not match\n", test_strings[i]);
        }
    }

    return 0;
}