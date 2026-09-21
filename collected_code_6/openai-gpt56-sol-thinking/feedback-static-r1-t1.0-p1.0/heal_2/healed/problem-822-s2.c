#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    MIN_PASSWORD_LENGTH = 8,
    MAX_PASSWORD_LENGTH = 128
};

static bool is_password_valid(const unsigned char *password, size_t length)
{
    bool has_uppercase = false;
    bool has_lowercase = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL ||
        length < (size_t)MIN_PASSWORD_LENGTH ||
        length > (size_t)MAX_PASSWORD_LENGTH) {
        return false;
    }

    for (size_t index = 0U; index < length; ++index) {
        const unsigned char character = password[index];

        if (character >= (unsigned char)'A' &&
            character <= (unsigned char)'Z') {
            has_uppercase = true;
        } else if (character >= (unsigned char)'a' &&
                   character <= (unsigned char)'z') {
            has_lowercase = true;
        } else if (character >= (unsigned char)'0' &&
                   character <= (unsigned char)'9') {
            has_digit = true;
        } else if (character >= (unsigned char)'!' &&
                   character <= (unsigned char)'~') {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_uppercase && has_lowercase && has_digit && has_special;
}

static void clear_buffer(void *buffer, size_t size)
{
    volatile unsigned char *position =
        (volatile unsigned char *)buffer;

    while (size > 0U) {
        *position = 0U;
        ++position;
        --size;
    }
}

int main(void)
{
    unsigned char password[MAX_PASSWORD_LENGTH + 2U];
    size_t length = 0U;
    bool malformed = false;
    bool valid;
    unsigned char character;

    while (fread(&character, sizeof character, 1U, stdin) == 1U) {
        if (character == (unsigned char)'\n') {
            break;
        }

        if (character == (unsigned char)'\0') {
            malformed = true;
        }

        if (length < sizeof password - 1U) {
            password[length] = character;
            ++length;
        } else {
            malformed = true;
        }
    }

    if (ferror(stdin) != 0) {
        clear_buffer(password, sizeof password);
        return EXIT_FAILURE;
    }

    if (length > 0U &&
        password[length - 1U] == (unsigned char)'\r') {
        --length;
    }

    if (length > (size_t)MAX_PASSWORD_LENGTH) {
        malformed = true;
    }

    password[length] = (unsigned char)'\0';
    valid = !malformed && is_password_valid(password, length);

    clear_buffer(password, sizeof password);

    if (fputs(valid ? "true\n" : "false\n", stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}