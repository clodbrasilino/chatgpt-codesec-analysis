#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_ERR_LEN 256

static void report_regex_error(int errcode, const regex_t *regex, const char *context)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char err_buf[MAX_ERR_LEN];

    memset(err_buf, 0, sizeof(err_buf));
    regerror(errcode, regex, err_buf, sizeof(err_buf));
    err_buf[sizeof(err_buf) - 1] = '\0';
    fprintf(stderr, "%s failed: %s\n", context, err_buf);
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