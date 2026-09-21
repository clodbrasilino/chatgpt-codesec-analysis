#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096
#define ERRBUF_SIZE 128

static void print_regex_error(int errcode, const regex_t *regex, const char *context)
{
    char errbuf[ERRBUF_SIZE];

    memset(errbuf, 0, sizeof(errbuf));
    regerror(errcode, regex, errbuf, sizeof(errbuf) - 1);
    errbuf[sizeof(errbuf) - 1] = '\0';
    fprintf(stderr, "%s: %s\n", context, errbuf);
}

int starts_and_ends_same(const char *str)
{
    regex_t regex;
    int ret;
    int result;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    len = strnlen(str, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input string too long or not null-terminated\n");
        return -1;
    }

    if (len == 0) {
        return 0;
    }

    if (len == 1) {
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