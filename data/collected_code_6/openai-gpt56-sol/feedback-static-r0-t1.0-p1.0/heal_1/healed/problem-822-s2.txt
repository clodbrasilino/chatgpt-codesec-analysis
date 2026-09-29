#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum {
    MIN_PASSWORD_LENGTH = 8,
    MAX_PASSWORD_LENGTH = 128
};

static bool is_valid_password(const char *password, size_t length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL ||
        length < MIN_PASSWORD_LENGTH ||
        length > MAX_PASSWORD_LENGTH) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        const unsigned char character = (unsigned char)password[i];

        if (character >= (unsigned char)'A' &&
            character <= (unsigned char)'Z') {
            has_upper = true;
        } else if (character >= (unsigned char)'a' &&
                   character <= (unsigned char)'z') {
            has_lower = true;
        } else if (character >= (unsigned char)'0' &&
                   character <= (unsigned char)'9') {
            has_digit = true;
        } else if (character >= 33U && character <= 126U) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main(void)
{
    char password[MAX_PASSWORD_LENGTH + 1U];
    size_t length = 0U;
    int character;
    bool too_long = false;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length < MAX_PASSWORD_LENGTH) {
            password[length++] = (char)character;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (character == EOF && length == 0U && !too_long) {
        return 1;
    }

    if (too_long) {
        puts("false");
        return 0;
    }

    password[length] = '\0';

    puts(is_valid_password(password, length) ? "true" : "false");
    return 0;
}