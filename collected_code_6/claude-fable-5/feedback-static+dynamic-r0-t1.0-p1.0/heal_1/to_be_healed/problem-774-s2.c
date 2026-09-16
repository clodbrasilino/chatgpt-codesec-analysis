#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int is_valid_email(const char *email)
{
    regex_t regex;
    int ret;
    const char *pattern = "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$";

    if (email == NULL) {
        return 0;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return -1;
    }

    ret = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    }

    return -1;
}

int main(void)
{
    const char *tests[] = {
        "user@example.com",
        "john.doe@mail.co.uk",
        "invalid-email",
        "missing@domain",
        "@nouser.com",
        "user@.com",
        "user+tag@sub.domain.org"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    int result;

    for (i = 0; i < count; i++) {
        result = is_valid_email(tests[i]);
        if (result == -1) {
            if (fprintf(stderr, "Regex error while checking: %s\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }
        if (printf("%s -> %s\n", tests[i], result == 1 ? "valid" : "invalid") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}