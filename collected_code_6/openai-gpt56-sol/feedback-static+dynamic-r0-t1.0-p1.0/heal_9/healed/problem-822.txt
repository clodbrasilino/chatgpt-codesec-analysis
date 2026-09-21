#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MIN_PASSWORD_LENGTH = 8,
    MAX_PASSWORD_LENGTH = 128,
    INPUT_BUFFER_SIZE = MAX_PASSWORD_LENGTH + 2
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
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return 0;
        }
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_password(char **password, size_t *length)
{
    char buffer[INPUT_BUFFER_SIZE];

    if (password == NULL || length == NULL) {
        return -1;
    }

    *password = NULL;
    *length = 0;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    size_t used = strcspn(buffer, "\n");
    const bool has_newline = buffer[used] == '\n';

    if (has_newline) {
        buffer[used] = '\0';
    } else if (!feof(stdin)) {
        if (discard_line() != 0) {
            return -1;
        }
        return 0;
    }

    if (used > 0 && buffer[used - 1] == '\r') {
        buffer[--used] = '\0';
    }

    if (used > MAX_PASSWORD_LENGTH) {
        return 0;
    }

    char *copy = malloc(used + 1);
    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, buffer, used + 1);

    *password = copy;
    *length = used;
    return 1;
}

int main(void)
{
    char *password = NULL;
    size_t length = 0;
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