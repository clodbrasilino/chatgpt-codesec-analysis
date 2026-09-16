#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#define MIN_PASSWORD_LENGTH 8U
#define MAX_PASSWORD_LENGTH 64U

bool is_valid_password(const char *password)
{
    size_t length;
    size_t i;
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL) {
        return false;
    }

    length = strnlen(password, MAX_PASSWORD_LENGTH + 1U);

    if ((length < MIN_PASSWORD_LENGTH) || (length > MAX_PASSWORD_LENGTH)) {
        return false;
    }

    for (i = 0U; i < length; i++) {
        unsigned char c = (unsigned char)password[i];

        if (!isprint(c) || isspace(c)) {
            return false;
        }

        if (isupper(c)) {
            has_upper = true;
        } else if (islower(c)) {
            has_lower = true;
        } else if (isdigit(c)) {
            has_digit = true;
        } else {
            has_special = true;
        }
    }

    return (has_upper && has_lower && has_digit && has_special);
}

int main(void)
{
    const char *test_passwords[] = {
        "Abcdef1!",
        "short1A!",
        "alllowercase1!",
        "ALLUPPERCASE1!",
        "NoDigits!!",
        "NoSpecial123",
        "Valid$Password9",
        "",
        "Has Space1!",
        NULL
    };
    size_t count = sizeof(test_passwords) / sizeof(test_passwords[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        bool result = is_valid_password(test_passwords[i]);

        if (test_passwords[i] != NULL) {
            if (printf("Password \"%s\": %s\n",
                       test_passwords[i],
                       result ? "valid" : "invalid") < 0) {
                return 1;
            }
        } else {
            if (printf("Password (NULL): %s\n",
                       result ? "valid" : "invalid") < 0) {
                return 1;
            }
        }
    }

    return 0;
}