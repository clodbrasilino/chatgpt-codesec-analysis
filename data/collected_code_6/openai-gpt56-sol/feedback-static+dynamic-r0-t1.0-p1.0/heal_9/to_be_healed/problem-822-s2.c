#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

static int read_password(char **password, size_t *length)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_BUFFER_SIZE];
    size_t used = 0;
    int character;

    if (password == NULL || length == NULL) {
        return -1;
    }

    *password = NULL;
    *length = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF &&
           character != '\n' &&
           character != '\r') {
        if (used < MAX_PASSWORD_LENGTH + 1U) {
            buffer[used++] = (char)character;
        }
    }

    if (character == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            if (ungetc(character, stdin) == EOF) {
                return -1;
            }
        }
    }

    if (character == EOF && ferror(stdin)) {
        return -1;
    }

    if (used > MAX_PASSWORD_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((character = fgetc(stdin)) != EOF &&
               character != '\n' &&
               character != '\r') {
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = fgetc(stdin);

            if (character != '\n' && character != EOF &&
                ungetc(character, stdin) == EOF) {
                return -1;
            }
        }

        if (character == EOF && ferror(stdin)) {
            return -1;
        }

        return 0;
    }

    if (used == 0 && character == EOF) {
        return 0;
    }

    char *result = malloc(used + 1U);

    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < used; ++i) {
        result[i] = buffer[i];
    }

    result[used] = '\0';
    *password = result;
    *length = used;

    return 1;
}

int main(void)
{
    char *password = NULL;
    size_t length = 0;
    const int result = read_password(&password, &length);

    if (result < 0) {
        free(password);
        return EXIT_FAILURE;
    }

    if (result == 0) {
        puts("false");
        free(password);
        return EXIT_SUCCESS;
    }

    puts(is_valid_password(password, length) ? "true" : "false");
    free(password);

    return EXIT_SUCCESS;
}