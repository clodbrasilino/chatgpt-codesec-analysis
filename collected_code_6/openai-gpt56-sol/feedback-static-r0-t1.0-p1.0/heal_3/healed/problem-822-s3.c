#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

enum {
    MINIMUM_PASSWORD_LENGTH = 8,
    MAXIMUM_PASSWORD_LENGTH = 128,
    PASSWORD_BUFFER_SIZE = MAXIMUM_PASSWORD_LENGTH + 2
};

static bool is_password_valid(const char *password, size_t length)
{
    bool has_lowercase = false;
    bool has_uppercase = false;
    bool has_digit = false;
    bool has_special = false;
    static const char special_characters[] = "!@#$%^&*()-_=+[]{};:,.?/";

    if (password == NULL ||
        length < MINIMUM_PASSWORD_LENGTH ||
        length > MAXIMUM_PASSWORD_LENGTH) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)password[i];

        if (character >= (unsigned char)'a' &&
            character <= (unsigned char)'z') {
            has_lowercase = true;
        } else if (character >= (unsigned char)'A' &&
                   character <= (unsigned char)'Z') {
            has_uppercase = true;
        } else if (character >= (unsigned char)'0' &&
                   character <= (unsigned char)'9') {
            has_digit = true;
        } else if (strchr(special_characters, character) != NULL) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_lowercase && has_uppercase && has_digit && has_special;
}

static bool consume_line_ending(void)
{
    int character = getchar();

    if (character == '\n') {
        return true;
    }

    if (character == '\r') {
        character = getchar();

        if (character == '\n') {
            return true;
        }

        if (character != EOF) {
            ungetc(character, stdin);
        }

        return true;
    }

    if (character != EOF) {
        ungetc(character, stdin);
    }

    return false;
}

int main(void)
{
    char password[PASSWORD_BUFFER_SIZE] = {0};
    size_t length;

    if (fgets(password, sizeof password, stdin) == NULL) {
        return 1;
    }

    length = strcspn(password, "\r\n");

    if (length < sizeof password && password[length] != '\0') {
        password[length] = '\0';
    } else if (length == sizeof password - 1U) {
        if (!consume_line_ending()) {
            puts("false");
            return ferror(stdin) ? 1 : 0;
        }
    }

    puts(is_password_valid(password, length) ? "true" : "false");
    return 0;
}