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

static bool is_password_valid(const char *password)
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
                            int character)
{
    if (password == NULL || length == NULL || capacity == 0) {
        return false;
    }

    if (*length >= capacity - 1 || character == '\0') {
        return false;
    }

    password[*length] = (char)(unsigned char)character;
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
    int character;

    password = malloc(PASSWORD_BUFFER_SIZE);
    if (password == NULL) {
        return EXIT_FAILURE;
    }

    password[0] = '\0';

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
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

    valid = input_valid && is_password_valid(password);

    clear_password(password, PASSWORD_BUFFER_SIZE);
    free(password);

    if (puts(valid ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}