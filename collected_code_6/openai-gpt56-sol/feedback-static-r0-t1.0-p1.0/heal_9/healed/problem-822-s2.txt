#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    MIN_PASSWORD_LENGTH = 8,
    MAX_PASSWORD_LENGTH = 128,
    INPUT_CAPACITY = MAX_PASSWORD_LENGTH + 2
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
        unsigned char character = (unsigned char)password[i];

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

static int read_password(char *password, size_t capacity, size_t *length)
{
    if (password == NULL || length == NULL || capacity < 2U) {
        return -1;
    }

    password[0] = '\0';
    *length = 0U;

    if (fgets(password, (int)capacity, stdin) == NULL) {
        return ferror(stdin) ? -1 : 1;
    }

    size_t used = 0U;

    while (used < capacity && password[used] != '\0') {
        ++used;
    }

    if (used == capacity) {
        password[0] = '\0';
        return -1;
    }

    if (used > 0U && password[used - 1U] == '\n') {
        --used;

        if (used > 0U && password[used - 1U] == '\r') {
            --used;
        }

        password[used] = '\0';
    } else {
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            password[0] = '\0';

            if (character == EOF && ferror(stdin)) {
                return -1;
            }

            return 0;
        }

        if (character == EOF && ferror(stdin)) {
            password[0] = '\0';
            return -1;
        }
    }

    *length = used;
    return 1;
}

int main(void)
{
    char *password = malloc((size_t)INPUT_CAPACITY);

    if (password == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = 0U;
    int result = read_password(password, (size_t)INPUT_CAPACITY, &length);

    if (result < 0) {
        free(password);
        return EXIT_FAILURE;
    }

    bool valid = result > 0 && is_valid_password(password, length);
    puts(valid ? "true" : "false");

    free(password);
    return EXIT_SUCCESS;
}