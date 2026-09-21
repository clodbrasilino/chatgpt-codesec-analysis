#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    MIN_PASSWORD_LENGTH = 8,
    MAX_PASSWORD_LENGTH = 128,
    PASSWORD_CAPACITY = MAX_PASSWORD_LENGTH + 2
};

bool is_password_valid(const char *password)
{
    size_t length = 0U;
    bool has_uppercase = false;
    bool has_lowercase = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL) {
        return false;
    }

    while (password[length] != '\0') {
        unsigned char character;

        if (length >= (size_t)MAX_PASSWORD_LENGTH) {
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

    return length >= (size_t)MIN_PASSWORD_LENGTH &&
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char password[PASSWORD_CAPACITY];
    size_t length = 0U;
    bool malformed = false;
    bool input_error = false;
    bool valid;

    for (;;) {
        unsigned char character;
        size_t count = fread(&character, sizeof character, 1U, stdin);

        if (count == 0U) {
            if (ferror(stdin) != 0) {
                input_error = true;
            }
            break;
        }

        if (character == (unsigned char)'\n') {
            break;
        }

        if (character == (unsigned char)'\0') {
            malformed = true;
            break;
        }

        if (length >= (size_t)PASSWORD_CAPACITY - 1U) {
            malformed = true;
            break;
        }

        password[length] = character;
        ++length;
    }

    if (input_error) {
        clear_buffer(password, sizeof password);
        return EXIT_FAILURE;
    }

    if (length > 0U &&
        password[length - 1U] == (unsigned char)'\r') {
        --length;
    }

    if (length > (size_t)MAX_PASSWORD_LENGTH) {
        malformed = true;
    }

    password[length] = (unsigned char)'\0';

    valid = !malformed && is_password_valid((const char *)password);

    clear_buffer(password, sizeof password);

    if (fputs(valid ? "true\n" : "false\n", stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}