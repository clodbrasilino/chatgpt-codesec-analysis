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
    static const char special_characters[] = "!@#$%^&*()-_=+[]{};:,.?/";
    bool has_lowercase = false;
    bool has_uppercase = false;
    bool has_digit = false;
    bool has_special = false;

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
        } else if (strchr(special_characters, (int)character) != NULL) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_lowercase && has_uppercase && has_digit && has_special;
}

static bool read_password(char *buffer, size_t capacity, size_t *length)
{
    if (buffer == NULL || length == NULL ||
        capacity < (size_t)MAXIMUM_PASSWORD_LENGTH + 2U) {
        return false;
    }

    size_t used = 0;
    bool too_long = false;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (character == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    return false;
                }
            }

            character = '\n';
            break;
        }

        if (used < (size_t)MAXIMUM_PASSWORD_LENGTH) {
            buffer[used++] = (char)character;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin) || (character == EOF && used == 0U && !too_long)) {
        return false;
    }

    buffer[used] = '\0';
    *length = used;

    return !too_long;
}

int main(void)
{
    char password[PASSWORD_BUFFER_SIZE];
    size_t length;

    if (!read_password(password, sizeof password, &length)) {
        if (ferror(stdin) || feof(stdin)) {
            return 1;
        }

        puts("false");
        return 0;
    }

    puts(is_password_valid(password, length) ? "true" : "false");
    return 0;
}