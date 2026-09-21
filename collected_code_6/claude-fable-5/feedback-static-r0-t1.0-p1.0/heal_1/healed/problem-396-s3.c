#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int starts_and_ends_same(const char *str)
{
    regex_t regex;
    int ret;
    const char *pattern = "^\\(.\\)\\(.*\\1\\)\\{0,1\\}$";

    if (str == NULL) {
        return -1;
    }

    ret = regcomp(&regex, pattern, 0);
    if (ret != 0) {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        errbuf[sizeof(errbuf) - 1] = '\0';
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    }
    if (ret == REG_NOMATCH) {
        return 0;
    }

    fprintf(stderr, "regexec failed with code %d\n", ret);
    return -1;
}

int main(void)
{
    const char *tests[] = {
        "abca",
        "abc",
        "a",
        "aa",
        "hello",
        "level",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = starts_and_ends_same(tests[i]);
        if (result < 0) {
            fprintf(stderr, "Error processing string \"%s\"\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (result == 1) {
            printf("\"%s\" starts and ends with the same character\n", tests[i]);
        } else {
            printf("\"%s\" does not start and end with the same character\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}