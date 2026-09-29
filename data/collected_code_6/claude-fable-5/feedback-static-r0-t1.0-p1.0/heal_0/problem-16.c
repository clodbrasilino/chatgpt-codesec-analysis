#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_ERROR_MSG 128

int match_lowercase_underscore(const char *text, int *result)
{
    regex_t regex;
    int rc;
    char error_msg[MAX_ERROR_MSG];
    const char *pattern = "^[a-z]+(_[a-z]+)+$";

    if (text == NULL || result == NULL) {
        return -1;
    }

    rc = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (rc != 0) {
        regerror(rc, &regex, error_msg, sizeof(error_msg));
        fprintf(stderr, "Regex compilation failed: %s\n", error_msg);
        return -1;
    }

    rc = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (rc == 0) {
        *result = 1;
        return 0;
    } else if (rc == REG_NOMATCH) {
        *result = 0;
        return 0;
    } else {
        fprintf(stderr, "Regex execution failed\n");
        return -1;
    }
}

int main(void)
{
    const char *tests[] = {
        "aab_cbbbc",
        "aab_Abbbc",
        "Aaab_abbbc",
        "hello_world_test",
        "no_underscore",
        "single",
        "with_UPPER_case"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    int result;

    for (i = 0; i < count; i++) {
        if (match_lowercase_underscore(tests[i], &result) != 0) {
            fprintf(stderr, "Error processing string: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (result == 1) {
            printf("\"%s\": Found a match\n", tests[i]);
        } else {
            printf("\"%s\": Not matched\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}