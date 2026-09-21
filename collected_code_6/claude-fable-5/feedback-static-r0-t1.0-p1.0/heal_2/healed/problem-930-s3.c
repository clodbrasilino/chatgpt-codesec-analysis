#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_a_followed_by_bs(const char *text)
{
    regex_t regex;
    int ret;

    if (text == NULL) {
        return 0;
    }

    ret = regcomp(&regex, "^ab*$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        size_t needed = regerror(ret, &regex, NULL, 0);
        char *errbuf = malloc(needed);
        if (errbuf != NULL) {
            regerror(ret, &regex, errbuf, needed);
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
    const char *tests[] = { "a", "ab", "abbbb", "b", "abc", "aab", "" };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = match_a_followed_by_bs(tests[i]);
        if (result < 0) {
            return EXIT_FAILURE;
        }
        printf("\"%s\": %s\n", tests[i], result == 1 ? "match" : "no match");
    }

    return EXIT_SUCCESS;
}