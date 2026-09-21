#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool is_valid_email(const char *email)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?)+$";
    regex_t regex;
    int status;

    if (email == NULL || *email == '\0') {
        return false;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return false;
    }

    status = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return status == 0;
}

int main(void)
{
    char email[255];
    size_t length;

    if (fgets(email, sizeof email, stdin) == NULL) {
        return 1;
    }

    length = strcspn(email, "\r\n");

    if (email[length] == '\0' && length == sizeof email - 1) {
        int ch;

        ch = getchar();
        if (ch != '\n' && ch != '\r' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            puts("Invalid email address");
            return 0;
        }
    }

    email[length] = '\0';

    if (is_valid_email(email)) {
        puts("Valid email address");
    } else {
        puts("Invalid email address");
    }

    return 0;
}