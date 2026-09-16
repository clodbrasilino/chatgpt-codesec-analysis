#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_pattern(const char *text)
{
    regex_t regex;
    int ret;
    char error_buffer[256];

    ret = regcomp(&regex, "a.*b$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        regerror(ret, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        return -1;
    }

    ret = regexec(&regex, text, 0, NULL, 0);

    if (ret == 0) {
        regfree(&regex);
        return 1;
    } else if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    } else {
        regerror(ret, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex execution failed: %s\n", error_buffer);
        regfree(&regex);
        return -1;
    }
}

int main(void)
{
    const char *tests[] = {
        "acb",
        "ab",
        "axyzb",
        "a123b",
        "bca",
        "abc",
        "b",
        "a"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = match_pattern(tests[i]);
        if (result < 0) {
            return EXIT_FAILURE;
        }
        if (result == 1) {
            printf("\"%s\" matches\n", tests[i]);
        } else {
            printf("\"%s\" does not match\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}