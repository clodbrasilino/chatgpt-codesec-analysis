#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_a_followed_by_two_to_three_b(const char *text)
{
    regex_t regex;
    int ret;

    if (text == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "ab{2,3}", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    }
    if (ret == REG_NOMATCH) {
        return 0;
    }
    return -1;
}

int main(void)
{
    const char *tests[] = {
        "ab",
        "abb",
        "abbb",
        "abbbb",
        "xxabbxx",
        "aab",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    int result;

    for (i = 0; i < count; i++) {
        result = match_a_followed_by_two_to_three_b(tests[i]);
        if (result < 0) {
            fprintf(stderr, "Error processing string: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (result == 1) {
            printf("\"%s\": match\n", tests[i]);
        } else {
            printf("\"%s\": no match\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}