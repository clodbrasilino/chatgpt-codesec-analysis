#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void print_regex_error(int errcode, const regex_t *regex, const char *context)
{
    size_t needed = regerror(errcode, regex, NULL, 0);
    char *errbuf = malloc(needed);

    if (errbuf != NULL) {
        regerror(errcode, regex, errbuf, needed);
        fprintf(stderr, "%s: %s\n", context, errbuf);
        free(errbuf);
    } else {
        fprintf(stderr, "%s: unable to allocate error buffer\n", context);
    }
}

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
        print_regex_error(ret, &regex, "Regex compilation failed");
        return -1;
    }

    ret = regexec(&regex, email, 0, NULL, 0);

    if (ret == 0) {
        regfree(&regex);
        return 1;
    } else if (ret == REG_NOMATCH) {
        regfree(&regex);
        return 0;
    } else {
        print_regex_error(ret, &regex, "Regex execution failed");
        regfree(&regex);
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

    for (i = 0; i < count; i++) {
        int result = is_valid_email(test_emails[i]);
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