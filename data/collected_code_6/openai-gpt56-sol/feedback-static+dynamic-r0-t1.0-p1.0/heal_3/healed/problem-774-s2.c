#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
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
    const char *end;
    int result;

    if (email == NULL || email[0] == '\0') {
        return false;
    }

    end = memchr(email, '\0', 255U);
    if (end == NULL || (size_t)(end - email) > 254U) {
        return false;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }

    result = regexec(&regex, email, 0U, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int main(int argc, char *const argv[])
{
    const char *const program_name =
        (argc > 0 && argv[0] != NULL) ? argv[0] : "email-validator";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email-address>\n", program_name);
        return EXIT_FAILURE;
    }

    if (is_valid_email(argv[1])) {
        puts("Valid email address");
        return EXIT_SUCCESS;
    }

    puts("Invalid email address");
    return EXIT_FAILURE;
}