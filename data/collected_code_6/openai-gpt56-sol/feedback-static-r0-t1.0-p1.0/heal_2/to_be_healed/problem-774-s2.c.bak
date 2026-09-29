#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_valid_email(const char *email)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]"
        "([A-Za-z0-9-]{0,61}[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]"
        "([A-Za-z0-9-]{0,61}[A-Za-z0-9])?)+$";
    regex_t regex;

    if (email == NULL || email[0] == '\0' || strlen(email) > 254U) {
        return false;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    const int result = regexec(&regex, email, 0U, NULL, 0);
    regfree(&regex);

    return result == 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email-address>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_valid_email(argv[1])) {
        puts("Valid email address");
        return EXIT_SUCCESS;
    }

    puts("Invalid email address");
    return EXIT_FAILURE;
}