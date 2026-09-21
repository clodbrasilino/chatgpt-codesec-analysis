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
    static const char special_characters[] = "!@#$%^&*()-_=+[]{};:,.?/";
    bool has_lowercase = false;
    bool has_uppercase = false;
    bool has_digit = false;
    bool has_special = false;
    size_t length = 0;

    if (password == NULL) {
        return false;
    }

    while (length <= MAXIMUM_PASSWORD_LENGTH && password[length] != '\0') {
        unsigned char character = (unsigned char)password[length];

        if (character >= (unsigned char)'a' &&
            character <= (unsigned char)'z') {
            has_lowercase = true;
        } else if (character >= (unsigned char)'A' &&
                   character <= (unsigned char)'Z') {
            has_uppercase = true;
        } else if (character >= (unsigned char)'0' &&
                   character <= (unsigned char)'9') {
            has_digit = true;
        } else if (strchr(special_characters, (int)character) != NULL) {
            has_special = true;
        } else {
            return false;
        }

        ++length;
    }

    if (length > MAXIMUM_PASSWORD_LENGTH) {
        return false;
    }

    return length >= MINIMUM_PASSWORD_LENGTH &&
           has_lowercase &&
           has_uppercase &&
           has_digit &&
           has_special;
}

static void discard_line(void)
{
    int character;

    do {
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);
}

int main(void)
{
    char password[PASSWORD_BUFFER_SIZE];

    if (fgets(password, sizeof password, stdin) == NULL) {
        return 1;
    }

    {
        size_t length = strcspn(password, "\r\n");

        if (password[length] == '\r' || password[length] == '\n') {
            int terminator = (unsigned char)password[length];

            password[length] = '\0';

            if (terminator == '\r' && password[length + 1] == '\n') {
                password[length + 1] = '\0';
            }
        } else if (!feof(stdin)) {
            discard_line();
            puts("false");
            return 0;
        }
    }

    puts(is_password_valid(password) ? "true" : "false");
    return 0;
}