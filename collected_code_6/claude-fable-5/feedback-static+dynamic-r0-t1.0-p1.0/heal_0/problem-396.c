#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int starts_and_ends_same(const char *str)
{
    regex_t regex;
    int ret;
    int result;

    if (str == NULL) {
        return -1;
    }

    if (str[0] == '\0') {
        return 0;
    }

    if (strlen(str) == 1) {
        return 1;
    }

    ret = regcomp(&regex, "^\\(.\\).*\\1$", 0);
    if (ret != 0) {
        char errbuf[128];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    } else if (ret == REG_NOMATCH) {
        result = 0;
    } else {
        char errbuf[128];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex execution failed: %s\n", errbuf);
        result = -1;
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *tests[] = {"abcba", "hello", "a", "xyzx", "test", ""};
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int res = starts_and_ends_same(tests[i]);
        if (res < 0) {
            fprintf(stderr, "Error processing string: \"%s\"\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (res == 1) {
            printf("\"%s\": starts and ends with the same character\n", tests[i]);
        } else {
            printf("\"%s\": does not start and end with the same character\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}