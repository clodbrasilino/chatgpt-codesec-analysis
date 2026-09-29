#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int is_valid_email(const char *email)
{
    regex_t regex;
    int result;
    const char *pattern = "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$";

    if (email == NULL) {
        return 0;
    }

    if (strlen(email) == 0 || strlen(email) > 254) {
        return 0;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        return 1;
    }

    return 0;
}

int main(void)
{
    const char *test_emails[] = {
        "user@example.com",
        "john.doe@company.org",
        "invalid-email",
        "missing@domain",
        "@nodomain.com",
        "user@sub.domain.co.uk",
        "spaces in@email.com",
        ""
    };
    size_t count = sizeof(test_emails) / sizeof(test_emails[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    int status;

    for (i = 0; i < count; i++) {
        status = is_valid_email(test_emails[i]);
        if (status == -1) {
            fprintf(stderr, "Error: failed to compile regex\n");
            return EXIT_FAILURE;
        }
        if (status == 1) {
            printf("\"%s\" is a valid email address\n", test_emails[i]);
        } else {
            printf("\"%s\" is NOT a valid email address\n", test_emails[i]);
        }
    }

    return EXIT_SUCCESS;
}