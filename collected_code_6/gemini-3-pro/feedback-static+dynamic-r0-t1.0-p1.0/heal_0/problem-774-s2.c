#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int is_valid_email(const char *email) {
    if (email == NULL) {
        return 0;
    }

    regex_t regex;
    int reti;
    const char *pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (!reti) {
        return 1;
    } else if (reti == REG_NOMATCH) {
        return 0;
    } else {
        return 0;
    }
}

int main(void) {
    const char *test_emails[] = {
        "user@example.com",
        "invalid.email",
        "john.doe@domain.co.uk",
        NULL
    };

    for (int i = 0; test_emails[i] != NULL; i++) {
        if (is_valid_email(test_emails[i])) {
            printf("%s is valid.\n", test_emails[i]);
        } else {
            printf("%s is invalid.\n", test_emails[i]);
        }
    }

    return 0;
}