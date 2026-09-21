#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    PASSWORD_MIN_LENGTH = 8,
    PASSWORD_MAX_LENGTH = 128,
    PASSWORD_BUFFER_SIZE = PASSWORD_MAX_LENGTH + 1
};

static bool is_password_valid(const unsigned char *password, size_t length)
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
        const unsigned char character = password[i];

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
        *data = 0U;
        ++data;
        --size;
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char password[PASSWORD_BUFFER_SIZE];
    size_t length = 0U;
    bool too_long = false;
    bool valid = false;
    int character = 0;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == '\n' || character == EOF) {
            break;
        }

        if (length < sizeof password) {
            password[length] = (unsigned char)character;
            ++length;
        } else {
            too_long = true;
        }
    }

    if (character == EOF && ferror(stdin)) {
        clear_password(password, sizeof password);
        return EXIT_FAILURE;
    }

    if (length > 0U && password[length - 1U] == (unsigned char)'\r') {
        --length;
    }

    if (!too_long) {
        valid = is_password_valid(password, length);
    }

    clear_password(password, sizeof password);

    if (puts(valid ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}