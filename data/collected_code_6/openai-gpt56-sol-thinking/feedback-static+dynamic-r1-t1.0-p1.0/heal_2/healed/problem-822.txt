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
        length < (size_t)PASSWORD_MIN_LENGTH ||
        length > (size_t)PASSWORD_MAX_LENGTH) {
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
        } else if (character >= 33U && character <= 126U) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_lowercase && has_uppercase && has_digit && has_special;
}

static void clear_password(void *password, size_t size)
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
    char password[PASSWORD_MAX_LENGTH + 1U];
    size_t length = 0U;
    bool too_long = false;
    bool valid;
    unsigned char character;

    for (;;) {
        size_t bytes_read = fread(&character, 1U, 1U, stdin);

        if (bytes_read == 0U) {
            if (ferror(stdin)) {
                clear_password(password, sizeof password);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == (unsigned char)'\n') {
            break;
        }

        if (length < sizeof password) {
            password[length++] = (char)character;
        } else {
            too_long = true;
        }
    }

    if (length > 0U && password[length - 1U] == '\r') {
        --length;
    }

    if (length > (size_t)PASSWORD_MAX_LENGTH) {
        too_long = true;
    }

    valid = !too_long && is_password_valid(password, length);

    clear_password(password, sizeof password);

    if (puts(valid ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}