#include <stdbool.h>
#include <stddef.h>
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
    size_t length;

    if (password == NULL) {
        return false;
    }

    length = strnlen(password, MAXIMUM_PASSWORD_LENGTH + 1);

    if (length < MINIMUM_PASSWORD_LENGTH ||
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

static bool read_password(char *buffer, size_t buffer_size)
{
    size_t length;

    if (buffer == NULL || buffer_size < 2) {
        return false;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return false;
    }

    length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\r' || buffer[length] == '\n') {
        buffer[length] = '\0';
        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    for (;;) {
        int character = getchar();

        if (character == '\n' || character == EOF) {
            break;
        }
    }

    buffer[0] = '\0';
    return true;
}

int main(void)
{
    char password[PASSWORD_BUFFER_SIZE] = {0};

    if (!read_password(password, sizeof password)) {
        return 1;
    }

    puts(is_password_valid(password) ? "true" : "false");
    return 0;
}