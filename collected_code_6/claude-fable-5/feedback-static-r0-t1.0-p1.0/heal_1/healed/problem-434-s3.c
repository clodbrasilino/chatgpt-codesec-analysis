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

    ret = regcomp(&regex, "ab+", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        size_t errbuf_size = regerror(ret, &regex, NULL, 0);
        char *errbuf = malloc(errbuf_size);
        if (errbuf != NULL) {
            regerror(ret, &regex, errbuf, errbuf_size);
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
    const char *tests[] = { "ab", "abbb", "a", "b", "ac", "xabby", "" };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = match_a_followed_by_bs(tests[i]);
        if (result < 0) {
            return EXIT_FAILURE;
        }
        if (result == 1) {
            printf("\"%s\" -> match\n", tests[i]);
        } else {
            printf("\"%s\" -> no match\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}