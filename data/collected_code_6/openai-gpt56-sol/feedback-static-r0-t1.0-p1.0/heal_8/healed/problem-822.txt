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

static int discard_line(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_password(char *password, size_t capacity, size_t *length)
{
    if (password == NULL || length == NULL || capacity < 2U) {
        return -1;
    }

    if (fgets(password, (int)capacity, stdin) == NULL) {
        return ferror(stdin) ? -1 : 2;
    }

    size_t used = 0U;

    while (used < capacity && password[used] != '\0' &&
           password[used] != '\n' && password[used] != '\r') {
        ++used;
    }

    if (used < capacity &&
        (password[used] == '\n' || password[used] == '\r')) {
        password[used] = '\0';
        *length = used;

        if (password[used] == '\r') {
            int character = getchar();

            if (character != '\n' && character != EOF) {
                if (discard_line() < 0) {
                    return -1;
                }
                return 0;
            }

            if (character == EOF && ferror(stdin)) {
                return -1;
            }
        }

        return 1;
    }

    if (used >= capacity - 1U) {
        if (discard_line() < 0) {
            return -1;
        }
        return 0;
    }

    password[used] = '\0';
    *length = used;
    return 1;
}

int main(void)
{
    char password[MAX_PASSWORD_LENGTH + 2U];
    size_t length = 0U;
    const int status = read_password(password, sizeof password, &length);

    if (status < 0) {
        return 1;
    }

    if (status == 2) {
        return 0;
    }

    if (status == 0) {
        puts("false");
        return 0;
    }

    puts(is_valid_password(password, length) ? "true" : "false");
    return 0;
}