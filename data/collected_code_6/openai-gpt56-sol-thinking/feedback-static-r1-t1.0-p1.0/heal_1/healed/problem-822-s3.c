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

static void clear_password(char *password, size_t size)
{
    volatile unsigned char *current;

    if (password == NULL) {
        return;
    }

    current = (volatile unsigned char *)password;

    while (size != 0) {
        *current++ = 0;
        --size;
    }
}

static void store_character(char *password,
                            size_t capacity,
                            size_t *length,
                            bool *input_valid,
                            int character)
{
    if (*length >= capacity - 1) {
        *input_valid = false;
        return;
    }

    if (character == '\0') {
        *input_valid = false;
    } else {
        password[*length] = (char)(unsigned char)character;
    }

    ++*length;
}

int main(void)
{
    char password[PASSWORD_BUFFER_SIZE] = {0};
    size_t length = 0;
    bool input_valid = true;
    bool pending_carriage_return = false;
    bool valid;
    int character;

    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            pending_carriage_return = false;
            break;
        }

        if (pending_carriage_return) {
            store_character(password,
                            sizeof(password),
                            &length,
                            &input_valid,
                            '\r');
            pending_carriage_return = false;
        }

        if (character == '\r') {
            pending_carriage_return = true;
            continue;
        }

        store_character(password,
                        sizeof(password),
                        &length,
                        &input_valid,
                        character);
    }

    if (ferror(stdin)) {
        clear_password(password, sizeof(password));
        return EXIT_FAILURE;
    }

    password[length] = '\0';
    valid = input_valid && is_password_valid(password);
    clear_password(password, sizeof(password));

    if (puts(valid ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}