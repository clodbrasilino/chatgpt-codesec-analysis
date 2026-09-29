#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

    for (size_t i = 0U; i < length; ++i) {
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

    do {
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    return ferror(stdin) ? -1 : 0;
}

static int read_password(char **password, size_t *length)
{
    char buffer[MAX_PASSWORD_LENGTH + 2U];
    size_t used;

    if (password == NULL || length == NULL) {
        return -1;
    }

    *password = NULL;
    *length = 0U;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    for (used = 0U; used < sizeof buffer && buffer[used] != '\0'; ++used) {
        if (buffer[used] == '\n') {
            buffer[used] = '\0';
            break;
        }
    }

    if (used > 0U && buffer[used - 1U] == '\r') {
        buffer[--used] = '\0';
    }

    if (used > MAX_PASSWORD_LENGTH) {
        if (buffer[MAX_PASSWORD_LENGTH + 1U] != '\n' &&
            discard_line() != 0) {
            return -1;
        }
        return 0;
    }

    if (used == MAX_PASSWORD_LENGTH &&
        buffer[used] != '\n' &&
        buffer[used] != '\0') {
        if (discard_line() != 0) {
            return -1;
        }
        return 0;
    }

    *password = malloc(used + 1U);
    if (*password == NULL) {
        return -1;
    }

    for (size_t i = 0U; i <= used; ++i) {
        (*password)[i] = buffer[i];
    }

    *length = used;
    return 1;
}

int main(void)
{
    char *password = NULL;
    size_t length = 0U;
    const int status = read_password(&password, &length);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status == 0) {
        puts("false");
        return EXIT_SUCCESS;
    }

    puts(is_valid_password(password, length) ? "true" : "false");
    free(password);

    return EXIT_SUCCESS;
}