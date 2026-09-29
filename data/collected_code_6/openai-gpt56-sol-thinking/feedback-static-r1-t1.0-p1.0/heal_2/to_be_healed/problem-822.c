#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    PASSWORD_MIN_LENGTH = 8,
    PASSWORD_MAX_LENGTH = 128
};

static bool is_password_valid(const char *password, size_t length)
{
    bool has_lowercase = false;
    bool has_uppercase = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL ||
        length < PASSWORD_MIN_LENGTH ||
        length > PASSWORD_MAX_LENGTH) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
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
        } else if (character >= 33U && character <= 126U) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_lowercase && has_uppercase && has_digit && has_special;
}

static void clear_password(void *password, size_t size)
{
    volatile unsigned char *data = password;

    while (size > 0U) {
        *data++ = 0U;
        --size;
    }
}

int main(void)
{
    const size_t capacity = (size_t)PASSWORD_MAX_LENGTH + 1U;
    char *password = malloc(capacity);
    size_t length = 0U;
    bool too_long = false;
    bool valid;
    int character;

    if (password == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length < capacity) {
            password[length++] = (char)(unsigned char)character;
        } else {
            too_long = true;
        }
    }

    if (character == EOF && ferror(stdin)) {
        clear_password(password, capacity);
        free(password);
        return EXIT_FAILURE;
    }

    if (length > 0U && password[length - 1U] == '\r') {
        --length;
    }

    valid = !too_long && is_password_valid(password, length);

    clear_password(password, capacity);
    free(password);

    if (puts(valid ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}