#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_lowercase_underscore(const char *text)
{
    regex_t re;
    int status;
    const char *pattern = "^[a-z]+_[a-z]+$";

    if (text == NULL) {
        return -1;
    }

    status = regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        size_t errbuf_size = regerror(status, &re, NULL, 0);
        char *errbuf = malloc(errbuf_size);
        if (errbuf != NULL) {
            regerror(status, &re, errbuf, errbuf_size);
            fprintf(stderr, "regcomp failed: %s\n", errbuf);
            free(errbuf);
        } else {
            fprintf(stderr, "regcomp failed and could not allocate error buffer\n");
        }
        return -1;
    }

    status = regexec(&re, text, 0, NULL, 0);
    regfree(&re);

    if (status == 0) {
        return 1;
    } else if (status == REG_NOMATCH) {
        return 0;
    } else {
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
        "no_underscore_here_",
        "abc"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = match_lowercase_underscore(tests[i]);
        if (result < 0) {
            fprintf(stderr, "Error processing string: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (result == 1) {
            printf("\"%s\" -> Found a match\n", tests[i]);
        } else {
            printf("\"%s\" -> Not matched\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}