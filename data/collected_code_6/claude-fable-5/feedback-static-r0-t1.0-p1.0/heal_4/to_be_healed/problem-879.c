#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERROR_BUFFER_SIZE 256

static void report_regex_error(int errcode, const regex_t *regex, const char *context)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char error_buffer[ERROR_BUFFER_SIZE];
    size_t needed;

    memset(error_buffer, 0, sizeof(error_buffer));
    needed = regerror(errcode, regex, error_buffer, sizeof(error_buffer) - 1);
    error_buffer[sizeof(error_buffer) - 1] = '\0';

    if (needed >= sizeof(error_buffer)) {
        fprintf(stderr, "%s: %s (message truncated)\n", context, error_buffer);
    } else {
        fprintf(stderr, "%s: %s\n", context, error_buffer);
    }
}

static int match_pattern(const char *text)
{
    regex_t regex;
    int ret;

    if (text == NULL) {
        fprintf(stderr, "match_pattern: NULL input\n");
        return -1;
    }

    ret = regcomp(&regex, "a.*b$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        report_regex_error(ret, &regex, "Regex compilation failed");
        regfree(&regex);
        return -1;
    }

    ret = regexec(&regex, text, 0, NULL, 0);

    if (ret == 0) {
        regfree(&regex);
        return 1;
    }

    if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    }

    report_regex_error(ret, &regex, "Regex execution failed");
    regfree(&regex);
    return -1;
}

int main(void)
{
    const char *tests[] = {
        "acb",
        "ab",
        "axyzb",
        "a123b",
        "bca",
        "abc",
        "b",
        "a"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = match_pattern(tests[i]);
        if (result < 0) {
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