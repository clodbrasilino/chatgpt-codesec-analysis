#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum {
    MAX_EMAIL_LENGTH = 320
};

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

static bool read_email(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    size_t length = strcspn(buffer, "\n");

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    int character;
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
    }

    buffer[0] = '\0';
    return false;
}

int main(void)
{
    char email[MAX_EMAIL_LENGTH + 1];

    if (!read_email(email, sizeof email)) {
        return 1;
    }

    puts(is_valid_email(email) ? "Valid" : "Invalid");
    return 0;
}