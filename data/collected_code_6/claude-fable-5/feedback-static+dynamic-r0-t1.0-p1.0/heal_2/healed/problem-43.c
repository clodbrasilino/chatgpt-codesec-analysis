#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_lowercase_underscore(const char *text)
{
    regex_t regex;
    int ret;

    if (text == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "^[a-z]+_[a-z]+$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        size_t errlen = regerror(ret, &regex, NULL, 0);
        char *errbuf = malloc(errlen);
        if (errbuf != NULL) {
            regerror(ret, &regex, errbuf, errlen);
            fprintf(stderr, "regcomp failed: %s\n", errbuf);
            free(errbuf);
        } else {
            fprintf(stderr, "regcomp failed and could not allocate error buffer\n");
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
        fprintf(stderr, "regexec failed\n");
        return -1;
    }
}

int main(void)
{
    const char *tests[] = {
        "aab_cbbbc",
        "aab_Abbbc",
        "Aaab_abbbc",
        "hello_world",
        "hello",
        "hello_world_again"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = match_lowercase_underscore(tests[i]);
        if (result < 0) {
            fprintf(stderr, "Error processing \"%s\"\n", tests[i]);
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