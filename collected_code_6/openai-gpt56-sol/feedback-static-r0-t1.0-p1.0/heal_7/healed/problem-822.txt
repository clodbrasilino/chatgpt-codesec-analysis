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
    size_t used = 0;
    bool complete = false;
    int character;

    if (password == NULL || length == NULL || capacity == 0U) {
        return -1;
    }

    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            complete = true;
            break;
        }

        if (character == '\r') {
            character = fgetc(stdin);

            if (character == EOF) {
                if (ferror(stdin)) {
                    return -1;
                }
            } else if (character != '\n') {
                do {
                    character = fgetc(stdin);
                } while (character != '\n' && character != EOF);

                if (ferror(stdin)) {
                    return -1;
                }

                return 0;
            }

            complete = true;
            break;
        }

        if (used + 1U >= capacity) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            if (ferror(stdin)) {
                return -1;
            }

            return 0;
        }

        password[used++] = (char)character;
    }

    if (ferror(stdin)) {
        return -1;
    }

    if (character == EOF && used == 0U && !complete) {
        return 2;
    }

    password[used] = '\0';
    *length = used;
    return 1;
}

int main(void)
{
    char password[MAX_PASSWORD_LENGTH + 1U];
    size_t length = 0U;
    int status = read_password(password, sizeof password, &length);

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