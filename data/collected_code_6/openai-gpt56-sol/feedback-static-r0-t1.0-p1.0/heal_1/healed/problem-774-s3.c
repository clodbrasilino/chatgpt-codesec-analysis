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

    if (email == NULL || *email == '\0') {
        return false;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    bool valid = regexec(&regex, email, 0, NULL, 0) == 0;
    regfree(&regex);

    return valid;
}

int main(void)
{
    char email[255];

    if (fgets(email, sizeof email, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(email, "\r\n");

    if (email[length] == '\0' && length == sizeof email - 1) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        puts("Invalid email address");
        return 0;
    }

    email[length] = '\0';

    puts(is_valid_email(email)
             ? "Valid email address"
             : "Invalid email address");

    return 0;
}