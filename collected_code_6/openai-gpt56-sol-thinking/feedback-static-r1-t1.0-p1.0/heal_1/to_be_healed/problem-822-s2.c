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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char password[MAX_PASSWORD_LENGTH + 2U];
    size_t length = 0;
    int character;
    bool malformed = false;
    bool valid;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (character == '\0') {
            malformed = true;
        }

        if (length < MAX_PASSWORD_LENGTH + 1U) {
            password[length] = (unsigned char)character;
            ++length;
        } else {
            malformed = true;
        }
    }

    if (character == EOF && ferror(stdin) != 0) {
        clear_buffer(password, sizeof(password));
        return EXIT_FAILURE;
    }

    if (length > 0U && password[length - 1U] == '\r') {
        --length;
    }

    if (length > MAX_PASSWORD_LENGTH) {
        malformed = true;
    }

    password[length] = '\0';

    valid = !malformed && is_password_valid((const char *)password);
    clear_buffer(password, sizeof(password));

    if (fputs(valid ? "true\n" : "false\n", stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}