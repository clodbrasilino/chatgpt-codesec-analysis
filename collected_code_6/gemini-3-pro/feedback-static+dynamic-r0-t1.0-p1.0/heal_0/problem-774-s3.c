#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int is_valid_email(const char *email) {
    if (email == NULL) {
        return 0;
    }

    regex_t regex;
    int reti;
    const char *pattern = "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$";

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
    const char *emails[] = {
        "test@example.com",
        "invalid-email",
        "user.name+tag@domain.co.uk",
        NULL
    };

    for (int i = 0; emails[i] != NULL; i++) {
        if (is_valid_email(emails[i])) {
            printf("Valid: %s\n", emails[i]);
        } else {
            printf("Invalid: %s\n", emails[i]);
        }
    }

    return 0;
}