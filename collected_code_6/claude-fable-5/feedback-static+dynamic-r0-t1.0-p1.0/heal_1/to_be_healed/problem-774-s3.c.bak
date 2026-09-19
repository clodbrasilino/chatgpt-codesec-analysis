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
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    ret = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex execution failed: %s\n", errbuf);
        return -1;
    }
}

int main(void)
{
    const char *test_emails[] = {
        "user@example.com",
        "john.doe@company.co.uk",
        "invalid.email",
        "@missing-local.org",
        "no-at-sign.com",
        "user@domain",
        "user+tag@example.io"
    };
    size_t count = sizeof(test_emails) / sizeof(test_emails[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    int result;

    for (i = 0; i < count; i++) {
        result = is_valid_email(test_emails[i]);
        if (result == 1) {
            printf("%s : valid\n", test_emails[i]);
        } else if (result == 0) {
            printf("%s : invalid\n", test_emails[i]);
        } else {
            fprintf(stderr, "Error validating: %s\n", test_emails[i]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}