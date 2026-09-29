#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    PASSWORD_MIN_LENGTH = 8,
    PASSWORD_MAX_LENGTH = 128,
    PASSWORD_BUFFER_SIZE = PASSWORD_MAX_LENGTH + 1
};

static bool is_password_valid(const char *password, size_t length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;
    size_t index;

    if (password == NULL ||
        length < PASSWORD_MIN_LENGTH ||
        length > PASSWORD_MAX_LENGTH) {
        return false;
    }

    for (index = 0; index < length; ++index) {
        unsigned char character = (unsigned char)password[index];

        if (!isprint(character) || isspace(character)) {
            return false;
        }

        if (isupper(character)) {
            has_upper = true;
        } else if (islower(character)) {
            has_lower = true;
        } else if (isdigit(character)) {
            has_digit = true;
        } else if (ispunct(character)) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

static void clear_password(void *buffer, size_t size)
{
    volatile unsigned char *current =
        (volatile unsigned char *)buffer;

    if (current == NULL) {
        return;
    }

    while (size > 0) {
        *current++ = 0;
        --size;
    }
}

static bool store_character(char *password,
                            size_t capacity,
                            size_t *length,
                            unsigned char character)
{
    if (password == NULL ||
        length == NULL ||
        capacity == 0 ||
        character == '\0' ||
        *length >= capacity - 1) {
        return false;
    }

    password[*length] = (char)character;
    ++*length;
    password[*length] = '\0';

    return true;
}

int main(void)
{
    char *password;
    size_t length = 0;
    bool input_valid = true;
    bool valid;
    unsigned char character;

    password = malloc(PASSWORD_BUFFER_SIZE);
    if (password == NULL) {
        return EXIT_FAILURE;
    }

    password[0] = '\0';

    while (fread(&character, sizeof character, 1, stdin) == 1) {
        if (character == '\n' || character == '\r') {
            break;
        }

        if (!store_character(password,
                             PASSWORD_BUFFER_SIZE,
                             &length,
                             character)) {
            input_valid = false;
        }
    }

    if (ferror(stdin)) {
        clear_password(password, PASSWORD_BUFFER_SIZE);
        free(password);
        return EXIT_FAILURE;
    }

    valid = input_valid && is_password_valid(password, length);

    clear_password(password, PASSWORD_BUFFER_SIZE);
    free(password);

    if (puts(valid ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}