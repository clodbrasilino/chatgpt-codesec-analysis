#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_lowercase_underscore(const char *text)
{
    regex_t regex;
    int ret;
    char errbuf[128];

    if (text == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "^[a-z]+_[a-z]+$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    ret = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    }
    if (ret == REG_NOMATCH) {
        return 0;
    }

    fprintf(stderr, "Regex execution failed\n");
    return -1;
}

int main(void)
{
    const char *tests[] = {
        "aab_cbbbc",
        "aab_Abbbc",
        "Aaab_abbbc",
        "hello_world",
        "no_underscore_here_ok"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    int result;

    for (i = 0; i < count; i++) {
        result = match_lowercase_underscore(tests[i]);
        if (result < 0) {
            fprintf(stderr, "Error processing string: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (result == 1) {
            printf("\"%s\": Found a match!\n", tests[i]);
        } else {
            printf("\"%s\": Not matched!\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}