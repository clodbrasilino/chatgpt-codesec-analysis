#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static void print_regex_error(int errcode, const regex_t *regex, const char *context)
{
    size_t needed;
    char *errbuf;

    needed = regerror(errcode, regex, NULL, 0);
    errbuf = malloc(needed);
    if (errbuf == NULL) {
        fprintf(stderr, "%s: unable to allocate error buffer\n", context);
        return;
    }
    regerror(errcode, regex, errbuf, needed);
    errbuf[needed - 1] = '\0';
    fprintf(stderr, "%s: %s\n", context, errbuf);
    free(errbuf);
}

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

    if (str[1] == '\0') {
        return 1;
    }

    ret = regcomp(&regex, "^\\(.\\).*\\1$", 0);
    if (ret != 0) {
        print_regex_error(ret, &regex, "Regex compilation failed");
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    if (ret == 0) {
        result = 1;
    } else if (ret == REG_NOMATCH) {
        result = 0;
    } else {
        print_regex_error(ret, &regex, "Regex execution failed");
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