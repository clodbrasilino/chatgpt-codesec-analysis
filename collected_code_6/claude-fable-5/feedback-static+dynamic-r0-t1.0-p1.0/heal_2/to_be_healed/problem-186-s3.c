#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_ERR_LEN 256

int search_literals(const char *text, const char *pattern, int *found)
{
    regex_t regex;
    int ret;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char err_buf[MAX_ERR_LEN];

    if (text == NULL || pattern == NULL || found == NULL) {
        return -1;
    }

    *found = 0;
    memset(err_buf, 0, sizeof(err_buf));

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        regerror(ret, &regex, err_buf, sizeof(err_buf));
        err_buf[sizeof(err_buf) - 1] = '\0';
        fprintf(stderr, "regcomp failed: %s\n", err_buf);
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

    regerror(ret, &regex, err_buf, sizeof(err_buf));
    err_buf[sizeof(err_buf) - 1] = '\0';
    regfree(&regex);
    fprintf(stderr, "regexec failed: %s\n", err_buf);
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