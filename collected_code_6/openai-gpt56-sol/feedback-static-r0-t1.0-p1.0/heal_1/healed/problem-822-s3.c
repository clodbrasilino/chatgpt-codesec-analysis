#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum {
    MINIMUM_PASSWORD_LENGTH = 8,
    MAXIMUM_PASSWORD_LENGTH = 128,
    PASSWORD_BUFFER_SIZE = MAXIMUM_PASSWORD_LENGTH + 2
};

static bool is_password_valid(const char *password)
{
    bool has_lowercase = false;
    bool has_uppercase = false;
    bool has_digit = false;
    bool has_special = false;
    size_t length;

    if (password == NULL) {
        return false;
    }

    length = strnlen(password, MAXIMUM_PASSWORD_LENGTH + 1U);

    if (length < MINIMUM_PASSWORD_LENGTH || length > MAXIMUM_PASSWORD_LENGTH) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        const unsigned char character = (unsigned char)password[i];

        if (character >= (unsigned char)'a' &&
            character <= (unsigned char)'z') {
            has_lowercase = true;
        } else if (character >= (unsigned char)'A' &&
                   character <= (unsigned char)'Z') {
            has_uppercase = true;
        } else if (character >= (unsigned char)'0' &&
                   character <= (unsigned char)'9') {
            has_digit = true;
        } else if (strchr("!@#$%^&*()-_=+[]{};:,.?/",
                          (int)character) != NULL) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_lowercase && has_uppercase && has_digit && has_special;
}

int main(void)
{
    char password[PASSWORD_BUFFER_SIZE];
    size_t length;

    if (fgets(password, sizeof password, stdin) == NULL) {
        return 1;
    }

    length = strcspn(password, "\r\n");

    if (password[length] != '\0') {
        password[length] = '\0';
    } else if (length == sizeof password - 1U) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        puts("false");
        return 0;
    }

    puts(is_password_valid(password) ? "true" : "false");
    return 0;
}