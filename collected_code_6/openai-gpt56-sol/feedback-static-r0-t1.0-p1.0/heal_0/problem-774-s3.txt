#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

static bool is_valid_email(const char *email)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9](?:[A-Za-z0-9-]{0,61}[A-Za-z0-9])?"
        "(?:\\.[A-Za-z0-9](?:[A-Za-z0-9-]{0,61}[A-Za-z0-9])?)+$";
    regex_t regex;
    int status;
    bool valid;

    if (email == NULL) {
        return false;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return false;
    }

    status = regexec(&regex, email, 0, NULL, 0);
    valid = status == 0;
    regfree(&regex);

    return valid;
}

int main(void)
{
    char email[255];

    if (fgets(email, sizeof(email), stdin) == NULL) {
        return 1;
    }

    email[strcspn(email, "\r\n")] = '\0';

    if (is_valid_email(email)) {
        puts("Valid email address");
    } else {
        puts("Invalid email address");
    }

    return 0;
}