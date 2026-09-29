#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    PASSWORD_MIN_LENGTH = 8,
    PASSWORD_MAX_LENGTH = 128
};

bool is_password_valid(const char *password)
{
    size_t length = 0;
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL) {
        return false;
    }

    while (password[length] != '\0') {
        unsigned char character;

        if (length >= PASSWORD_MAX_LENGTH) {
            return false;
        }

        character = (unsigned char)password[length];

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

        ++length;
    }

    return length >= PASSWORD_MIN_LENGTH &&
           has_upper &&
           has_lower &&
           has_digit &&
           has_special;
}

static void clear_password(void *buffer, size_t size)
{
    volatile unsigned char *current = buffer;

    while (size > 0) {
        *current++ = 0;
        --size;
    }
}

int main(void)
{
    const size_t capacity = (size_t)PASSWORD_MAX_LENGTH + 1U;
    char *password = calloc(capacity, sizeof(*password));
    size_t length = 0;
    bool input_valid = true;
    bool valid;
    unsigned char character;
    int result;

    if (password == NULL) {
        return EXIT_FAILURE;
    }

    while (fread(&character, sizeof(character), 1U, stdin) == 1U) {
        if (character == (unsigned char)'\n') {
            break;
        }

        if (character == (unsigned char)'\0') {
            input_valid = false;
        } else if (length < (size_t)PASSWORD_MAX_LENGTH) {
            password[length++] = (char)character;
        } else {
            input_valid = false;
        }
    }

    if (ferror(stdin)) {
        clear_password(password, capacity);
        free(password);
        return EXIT_FAILURE;
    }

    if (length > 0U && password[length - 1U] == '\r') {
        password[--length] = '\0';
    }

    password[length] = '\0';
    valid = input_valid && is_password_valid(password);

    clear_password(password, capacity);
    free(password);

    result = puts(valid ? "true" : "false");

    return result == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}