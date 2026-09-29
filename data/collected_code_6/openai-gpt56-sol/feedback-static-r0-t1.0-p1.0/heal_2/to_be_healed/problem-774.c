#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum { EMAIL_BUFFER_SIZE = 321 };

static bool is_valid_email(const char *email)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]([A-Za-z0-9-]*[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]([A-Za-z0-9-]*[A-Za-z0-9])?)+$";
    regex_t regex;

    if (email == NULL || email[0] == '\0') {
        return false;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    int result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char email[EMAIL_BUFFER_SIZE];

    if (fgets(email, sizeof email, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(email, "\n");

    if (email[length] == '\n') {
        email[length] = '\0';
    } else if (!feof(stdin)) {
        return 1;
    }

    if (length > 0 && email[length - 1] == '\r') {
        email[length - 1] = '\0';
    }

    puts(is_valid_email(email) ? "Valid" : "Invalid");
    return 0;
}