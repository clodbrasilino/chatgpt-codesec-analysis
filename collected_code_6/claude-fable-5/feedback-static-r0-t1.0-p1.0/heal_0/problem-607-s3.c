#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERR_BUF_SIZE 128

int search_pattern(const char *text, const char *pattern, regoff_t *start, regoff_t *end)
{
    regex_t regex;
    regmatch_t match;
    char err_buf[ERR_BUF_SIZE];
    int ret;

    if (text == NULL || pattern == NULL || start == NULL || end == NULL) {
        return -1;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, err_buf, sizeof(err_buf));
        fprintf(stderr, "Regex compilation failed: %s\n", err_buf);
        return -1;
    }

    ret = regexec(&regex, text, 1, &match, 0);
    if (ret == 0) {
        *start = match.rm_so;
        *end = match.rm_eo;
        regfree(&regex);
        return 0;
    } else if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 1;
    } else {
        regerror(ret, &regex, err_buf, sizeof(err_buf));
        fprintf(stderr, "Regex execution failed: %s\n", err_buf);
        regfree(&regex);
        return -1;
    }
}

int main(void)
{
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "brown fox";
    regoff_t start = 0;
    regoff_t end = 0;
    int result;

    result = search_pattern(text, pattern, &start, &end);

    if (result == 0) {
        printf("Pattern \"%s\" found in text.\n", pattern);
        printf("Match starts at index %lld and ends at index %lld.\n",
               (long long)start, (long long)end);
        printf("Matched substring: \"%.*s\"\n",
               (int)(end - start), text + start);
    } else if (result == 1) {
        printf("Pattern \"%s\" not found in text.\n", pattern);
    } else {
        fprintf(stderr, "An error occurred during pattern search.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}