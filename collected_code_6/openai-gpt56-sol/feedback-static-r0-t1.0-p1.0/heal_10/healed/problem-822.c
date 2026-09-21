#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum {
    MIN_PASSWORD_LENGTH = 8,
    MAX_PASSWORD_LENGTH = 128,
    PASSWORD_BUFFER_SIZE = MAX_PASSWORD_LENGTH + 2
};

typedef enum {
    READ_ERROR = -1,
    READ_TOO_LONG = 0,
    READ_OK = 1,
    READ_EOF = 2
} ReadStatus;

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

static int discard_line(FILE *stream)
{
    int character;

    if (stream == NULL) {
        return -1;
    }

    while ((character = getc(stream)) != '\n' && character != EOF) {
    }

    return ferror(stream) ? -1 : 0;
}

static ReadStatus read_password(FILE *stream, char *password,
                                size_t capacity, size_t *length)
{
    if (stream == NULL || password == NULL || length == NULL ||
        capacity < 2U || capacity > PASSWORD_BUFFER_SIZE) {
        return READ_ERROR;
    }

    password[0] = '\0';
    *length = 0U;

    if (fgets(password, (int)capacity, stream) == NULL) {
        return ferror(stream) ? READ_ERROR : READ_EOF;
    }

    size_t used = 0U;

    while (used < capacity && password[used] != '\0' &&
           password[used] != '\n' && password[used] != '\r') {
        ++used;
    }

    if (used == capacity) {
        password[0] = '\0';
        return READ_ERROR;
    }

    if (password[used] == '\n') {
        password[used] = '\0';
        *length = used;
        return READ_OK;
    }

    if (password[used] == '\r') {
        password[used] = '\0';
        *length = used;

        int character = getc(stream);

        if (character == '\n' || (character == EOF && !ferror(stream))) {
            return READ_OK;
        }

        if (character == EOF || discard_line(stream) < 0) {
            password[0] = '\0';
            *length = 0U;
            return READ_ERROR;
        }

        password[0] = '\0';
        *length = 0U;
        return READ_TOO_LONG;
    }

    if (used == capacity - 1U) {
        if (discard_line(stream) < 0) {
            password[0] = '\0';
            return READ_ERROR;
        }

        password[0] = '\0';
        return READ_TOO_LONG;
    }

    *length = used;
    return READ_OK;
}

int main(void)
{
    char password[PASSWORD_BUFFER_SIZE] = {0};
    size_t length = 0U;
    ReadStatus status =
        read_password(stdin, password, sizeof password, &length);

    if (status == READ_ERROR) {
        return 1;
    }

    if (status == READ_EOF) {
        return 0;
    }

    if (status == READ_TOO_LONG) {
        puts("false");
        return 0;
    }

    puts(is_valid_password(password, length) ? "true" : "false");
    return 0;
}