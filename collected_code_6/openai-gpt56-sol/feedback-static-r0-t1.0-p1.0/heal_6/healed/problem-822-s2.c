#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

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

static int discard_remainder(void)
{
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t i = 0;

        while (i < sizeof buffer && buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                return 0;
            }
            ++i;
        }
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_password(char *password, size_t capacity, size_t *length)
{
    size_t used = 0;

    if (password == NULL ||
        length == NULL ||
        capacity < 2U ||
        capacity > (size_t)INPUT_CAPACITY ||
        capacity > (size_t)INT_MAX) {
        return -1;
    }

    password[0] = '\0';
    *length = 0;

    if (fgets(password, (int)capacity, stdin) == NULL) {
        return ferror(stdin) ? -1 : 1;
    }

    while (used < capacity && password[used] != '\0' &&
           password[used] != '\n') {
        ++used;
    }

    if (used < capacity && password[used] == '\n') {
        password[used] = '\0';

        if (used > 0U && password[used - 1U] == '\r') {
            password[--used] = '\0';
        }

        *length = used;
        return 1;
    }

    if (used + 1U < capacity) {
        *length = used;
        return 1;
    }

    if (discard_remainder() < 0) {
        password[0] = '\0';
        return -1;
    }

    password[0] = '\0';
    return 0;
}

int main(void)
{
    char password[INPUT_CAPACITY] = {0};
    size_t length = 0;
    int result = read_password(password, sizeof password, &length);

    if (result < 0) {
        return 1;
    }

    if (result == 0) {
        puts("false");
        return 0;
    }

    puts(is_valid_password(password, length) ? "true" : "false");
    return 0;
}