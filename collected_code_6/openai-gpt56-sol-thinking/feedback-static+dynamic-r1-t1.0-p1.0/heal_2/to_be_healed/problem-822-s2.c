#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    MIN_PASSWORD_LENGTH = 8,
    MAX_PASSWORD_LENGTH = 128
};

bool is_password_valid(const char *password)
{
    size_t length = 0;
    bool has_uppercase = false;
    bool has_lowercase = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL) {
        return false;
    }

    while (password[length] != '\0') {
        unsigned char character;

        if (length >= MAX_PASSWORD_LENGTH) {
            return false;
        }

        character = (unsigned char)password[length];

        if (character >= (unsigned char)'A' &&
            character <= (unsigned char)'Z') {
            has_uppercase = true;
        } else if (character >= (unsigned char)'a' &&
                   character <= (unsigned char)'z') {
            has_lowercase = true;
        } else if (character >= (unsigned char)'0' &&
                   character <= (unsigned char)'9') {
            has_digit = true;
        } else if (character >= (unsigned char)'!' &&
                   character <= (unsigned char)'~') {
            has_special = true;
        } else {
            return false;
        }

        ++length;
    }

    return length >= MIN_PASSWORD_LENGTH &&
           has_uppercase &&
           has_lowercase &&
           has_digit &&
           has_special;
}

static void clear_buffer(void *buffer, size_t size)
{
    volatile unsigned char *position = buffer;

    while (size > 0U) {
        *position = 0U;
        ++position;
        --size;
    }
}

int main(void)
{
    const size_t capacity = (size_t)MAX_PASSWORD_LENGTH + 2U;
    unsigned char *password = malloc(capacity);
    size_t length = 0U;
    int character = EOF;
    bool malformed = false;
    bool valid;

    if (password == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            break;
        }

        if (character == '\0') {
            malformed = true;
        }

        if (length + 1U < capacity) {
            password[length] = (unsigned char)character;
            ++length;
        } else {
            malformed = true;
        }
    }

    if (character == EOF && ferror(stdin) != 0) {
        clear_buffer(password, capacity);
        free(password);
        return EXIT_FAILURE;
    }

    if (length > 0U && password[length - 1U] == (unsigned char)'\r') {
        --length;
    }

    if (length > (size_t)MAX_PASSWORD_LENGTH) {
        malformed = true;
    }

    password[length] = (unsigned char)'\0';

    valid = !malformed && is_password_valid((const char *)password);

    clear_buffer(password, capacity);
    free(password);

    if (fputs(valid ? "true\n" : "false\n", stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}