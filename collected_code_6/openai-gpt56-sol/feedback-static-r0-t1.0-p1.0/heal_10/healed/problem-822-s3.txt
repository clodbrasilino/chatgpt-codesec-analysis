#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

enum {
    MINIMUM_PASSWORD_LENGTH = 8,
    MAXIMUM_PASSWORD_LENGTH = 128,
    PASSWORD_BUFFER_SIZE = MAXIMUM_PASSWORD_LENGTH + 2
};

static bool is_password_valid(const char *password, size_t length)
{
    static const char special_characters[] = "!@#$%^&*()-_=+[]{};:,.?/";
    bool has_lowercase = false;
    bool has_uppercase = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL ||
        length < MINIMUM_PASSWORD_LENGTH ||
        length > MAXIMUM_PASSWORD_LENGTH) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)password[i];

        if (character >= (unsigned char)'a' &&
            character <= (unsigned char)'z') {
            has_lowercase = true;
        } else if (character >= (unsigned char)'A' &&
                   character <= (unsigned char)'Z') {
            has_uppercase = true;
        } else if (character >= (unsigned char)'0' &&
                   character <= (unsigned char)'9') {
            has_digit = true;
        } else if (strchr(special_characters, character) != NULL) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_lowercase && has_uppercase && has_digit && has_special;
}

static bool discard_line(void)
{
    int character;

    do {
        character = getchar();
    } while (character != '\n' && character != EOF);

    return !ferror(stdin);
}

static bool read_password(char *buffer, size_t capacity, size_t *length)
{
    if (buffer == NULL || length == NULL ||
        capacity < (size_t)PASSWORD_BUFFER_SIZE) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    size_t used = strcspn(buffer, "\r\n");

    if (buffer[used] == '\r') {
        if (buffer[used + 1U] == '\n') {
            buffer[used] = '\0';
        } else if (buffer[used + 1U] == '\0') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    return false;
                }
            }

            buffer[used] = '\0';
        } else {
            buffer[used] = '\0';
        }
    } else if (buffer[used] == '\n') {
        buffer[used] = '\0';
    } else if (used > MAXIMUM_PASSWORD_LENGTH) {
        if (!discard_line()) {
            return false;
        }

        buffer[MAXIMUM_PASSWORD_LENGTH] = '\0';
        *length = MAXIMUM_PASSWORD_LENGTH;
        return false;
    } else if (used == MAXIMUM_PASSWORD_LENGTH) {
        int next = getchar();

        if (next == '\r') {
            int following = getchar();

            if (following != '\n' && following != EOF &&
                ungetc(following, stdin) == EOF) {
                return false;
            }
        } else if (next != '\n' && next != EOF) {
            if (!discard_line()) {
                return false;
            }

            buffer[used] = '\0';
            *length = used;
            return false;
        }
    }

    if (ferror(stdin)) {
        return false;
    }

    buffer[used] = '\0';
    *length = used;
    return true;
}

int main(void)
{
    char password[PASSWORD_BUFFER_SIZE] = {0};
    size_t length = 0;

    if (!read_password(password, sizeof password, &length)) {
        if (ferror(stdin) || feof(stdin)) {
            return 1;
        }

        puts("false");
        return 0;
    }

    puts(is_password_valid(password, length) ? "true" : "false");
    return 0;
}