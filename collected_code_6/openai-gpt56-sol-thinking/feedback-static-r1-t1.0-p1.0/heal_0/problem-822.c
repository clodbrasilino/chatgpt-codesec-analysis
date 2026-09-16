#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    PASSWORD_MIN_LENGTH = 8,
    PASSWORD_MAX_LENGTH = 128
};

bool is_password_valid(const char *password, size_t length)
{
    bool has_lowercase = false;
    bool has_uppercase = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL ||
        length < PASSWORD_MIN_LENGTH ||
        length > PASSWORD_MAX_LENGTH) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)password[i];

        if (character >= 'a' && character <= 'z') {
            has_lowercase = true;
        } else if (character >= 'A' && character <= 'Z') {
            has_uppercase = true;
        } else if (character >= '0' && character <= '9') {
            has_digit = true;
        } else if (character >= 33U && character <= 126U) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_lowercase && has_uppercase && has_digit && has_special;
}

static void clear_password(char *password, size_t size)
{
    volatile unsigned char *data = (volatile unsigned char *)password;

    while (size > 0U) {
        *data = 0U;
        ++data;
        --size;
    }
}

int main(void)
{
    char password[PASSWORD_MAX_LENGTH];
    size_t length = 0U;
    bool too_long = false;
    bool valid;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length < sizeof(password)) {
            password[length++] = (char)character;
        } else {
            too_long = true;
        }
    }

    if (character == EOF && ferror(stdin)) {
        clear_password(password, sizeof(password));
        return EXIT_FAILURE;
    }

    if (length > 0U && password[length - 1U] == '\r') {
        --length;
    }

    valid = !too_long && is_password_valid(password, length);
    clear_password(password, sizeof(password));

    if (puts(valid ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}