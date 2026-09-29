#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_pattern(const char *text)
{
    regex_t regex;
    int ret;

    if (text == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "a.*b$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        size_t errlen = regerror(ret, &regex, NULL, 0);
        char *errbuf = malloc(errlen);
        if (errbuf != NULL) {
            regerror(ret, &regex, errbuf, errlen);
            fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
            free(errbuf);
        } else {
            fprintf(stderr, "Regex compilation failed\n");
        }
        return -1;
    }

    ret = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        fprintf(stderr, "Regex execution failed\n");
        return -1;
    }
}

int main(void)
{
    const char *tests[] = {
        "ab",
        "acb",
        "a123b",
        "abc",
        "xyz",
        "aXXXXb"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = match_pattern(tests[i]);
        if (result < 0) {
            fprintf(stderr, "Error matching string: %s\n", tests[i]);
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