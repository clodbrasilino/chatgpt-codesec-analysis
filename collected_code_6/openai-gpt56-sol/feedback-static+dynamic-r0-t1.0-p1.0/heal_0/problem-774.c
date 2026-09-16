#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

static bool is_valid_email(const char *email)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9](?:[A-Za-z0-9-]*[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9](?:[A-Za-z0-9-]*[A-Za-z0-9])?)+$";
    regex_t regex;
    int result;

    if (email == NULL) {
        return false;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }

    result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int main(void)
{
    char email[320];

    if (fgets(email, sizeof email, stdin) == NULL) {
        return 1;
    }

    size_t length = 0;
    while (email[length] != '\0' && email[length] != '\n') {
        ++length;
    }

    if (email[length] == '\n') {
        email[length] = '\0';
    } else if (email[length] != '\0') {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        return 1;
    }

    puts(is_valid_email(email) ? "Valid" : "Invalid");
    return 0;
}