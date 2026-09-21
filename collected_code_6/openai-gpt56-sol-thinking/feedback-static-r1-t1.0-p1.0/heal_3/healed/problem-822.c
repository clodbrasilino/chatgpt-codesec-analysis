#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    PASSWORD_MIN_LENGTH = 8,
    PASSWORD_MAX_LENGTH = 128,
    PASSWORD_BUFFER_SIZE = PASSWORD_MAX_LENGTH + 1
};

static bool is_password_valid(const unsigned char *password, size_t length)
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

    for (size_t i = 0U; i < length; ++i) {
        const unsigned char character = password[i];

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
    volatile unsigned char *data = password;

    while (size > 0U) {
        *data = 0U;
        ++data;
        --size;
    }
}

int main(void)
{
    unsigned char *password =
        malloc(PASSWORD_BUFFER_SIZE * sizeof *password);
    unsigned char character = 0U;
    size_t length = 0U;
    bool too_long = false;
    bool input_error = false;
    bool valid = false;

    if (password == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        const size_t count = fread(&character, sizeof character, 1U, stdin);

        if (count != 1U) {
            if (ferror(stdin) || !feof(stdin)) {
                input_error = true;
            }
            break;
        }

        if (character == (unsigned char)'\n') {
            break;
        }

        if (length >= PASSWORD_BUFFER_SIZE) {
            too_long = true;
            break;
        }

        password[length] = character;
        ++length;
    }

    clear_password(&character, sizeof character);

    if (input_error) {
        clear_password(password, PASSWORD_BUFFER_SIZE);
        free(password);
        return EXIT_FAILURE;
    }

    if (length > 0U &&
        password[length - 1U] == (unsigned char)'\r') {
        --length;
    }

    if (!too_long) {
        valid = is_password_valid(password, length);
    }

    clear_password(password, PASSWORD_BUFFER_SIZE);
    free(password);

    if (puts(valid ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}