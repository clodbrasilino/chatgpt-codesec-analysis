#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void report_regex_error(int errcode, const regex_t *regex, const char *context)
{
    size_t needed;
    char *err_buf;

    needed = regerror(errcode, regex, NULL, 0);
    if (needed == 0) {
        fprintf(stderr, "%s failed: unknown error\n", context);
        return;
    }

    err_buf = calloc(needed, sizeof(char));
    if (err_buf == NULL) {
        fprintf(stderr, "%s failed: unable to allocate error buffer\n", context);
        return;
    }

    regerror(errcode, regex, err_buf, needed);
    err_buf[needed - 1] = '\0';
    fprintf(stderr, "%s failed: %s\n", context, err_buf);
    free(err_buf);
}

int search_literals(const char *text, const char *pattern, int *found)
{
    regex_t regex;
    int ret;

    if (text == NULL || pattern == NULL || found == NULL) {
        return -1;
    }

    *found = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        report_regex_error(ret, &regex, "regcomp");
        return -1;
    }

    ret = regexec(&regex, text, 0, NULL, 0);

    if (ret == 0) {
        regfree(&regex);
        *found = 1;
        return 0;
    }

    if (ret == REG_NOMATCH) {
        regfree(&regex);
        *found = 0;
        return 0;
    }

    report_regex_error(ret, &regex, "regexec");
    regfree(&regex);
    return -1;
}

int main(void)
{
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "quick|lazy|missing";
    int found = 0;

    if (search_literals(text, pattern, &found) != 0) {
        fprintf(stderr, "Search operation failed\n");
        return EXIT_FAILURE;
    }

    if (found == 1) {
        if (printf("Match found in: \"%s\"\n", text) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No match found in: \"%s\"\n", text) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}