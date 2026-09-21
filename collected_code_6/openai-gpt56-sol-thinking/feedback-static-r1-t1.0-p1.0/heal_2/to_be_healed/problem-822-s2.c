#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    MIN_PASSWORD_LENGTH = 8,
    MAX_PASSWORD_LENGTH = 128
};

static bool is_password_valid(const unsigned char *password, size_t length)
{
    bool has_uppercase = false;
    bool has_lowercase = false;
    bool has_digit = false;
    bool has_special = false;
    size_t index;

    if (password == NULL ||
        length < MIN_PASSWORD_LENGTH ||
        length > MAX_PASSWORD_LENGTH) {
        return false;
    }

    for (index = 0U; index < length; ++index) {
        unsigned char character = password[index];

        if (character >= 'A' && character <= 'Z') {
            has_uppercase = true;
        } else if (character >= 'a' && character <= 'z') {
            has_lowercase = true;
        } else if (character >= '0' && character <= '9') {
            has_digit = true;
        } else if (character >= '!' && character <= '~') {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_uppercase && has_lowercase && has_digit && has_special;
}

static void clear_buffer(void *buffer, size_t size)
{
    volatile unsigned char *position = buffer;

    while (size > 0U) {
        *position++ = 0U;
        --size;
    }
}

int main(void)
{
    const size_t capacity = (size_t)MAX_PASSWORD_LENGTH + 2U;
    unsigned char *password = malloc(capacity);
    size_t length = 0U;
    int character;
    bool malformed = false;
    bool valid;

    if (password == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (character == '\0') {
            malformed = true;
        }

        if (length < capacity - 1U) {
            password[length++] = (unsigned char)character;
        } else {
            malformed = true;
        }
    }

    if (character == EOF && ferror(stdin) != 0) {
        clear_buffer(password, capacity);
        free(password);
        return EXIT_FAILURE;
    }

    if (length > 0U && password[length - 1U] == '\r') {
        --length;
    }

    if (length > MAX_PASSWORD_LENGTH) {
        malformed = true;
    }

    password[length] = '\0';
    valid = !malformed && is_password_valid(password, length);

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