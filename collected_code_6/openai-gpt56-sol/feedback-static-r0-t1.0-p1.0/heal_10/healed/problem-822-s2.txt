#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int discard_line(void)
{
    char buffer[256];

    for (;;) {
        if (fgets(buffer, (int)sizeof buffer, stdin) == NULL) {
            return ferror(stdin) ? -1 : 0;
        }

        if (strchr(buffer, '\n') != NULL) {
            return 0;
        }
    }
}

static int read_password(char *password, size_t capacity, size_t *length)
{
    if (password == NULL ||
        length == NULL ||
        capacity < 2U ||
        capacity > (size_t)INT_MAX) {
        return -1;
    }

    password[0] = '\0';
    *length = 0U;

    if (fgets(password, (int)capacity, stdin) == NULL) {
        return ferror(stdin) ? -1 : 1;
    }

    size_t used = strnlen(password, capacity);

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
    } else if (!feof(stdin)) {
        int status = discard_line();

        password[0] = '\0';

        if (status < 0) {
            return -1;
        }

        return 0;
    }

    *length = used;
    return 1;
}

int main(void)
{
    char password[INPUT_CAPACITY];
    size_t length = 0U;
    int result = read_password(password, sizeof password, &length);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    puts(result > 0 && is_valid_password(password, length)
             ? "true"
             : "false");

    return EXIT_SUCCESS;
}