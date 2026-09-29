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
    char *buffer = NULL;
    size_t capacity = 0U;
    size_t used = 0U;
    int character;

    if (password == NULL || length == NULL) {
        return -1;
    }

    *password = NULL;
    *length = 0U;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            const int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    free(buffer);
                    return -1;
                }
            } else if (next == EOF && ferror(stdin)) {
                free(buffer);
                return -1;
            }

            break;
        }

        if (used == MAX_PASSWORD_LENGTH) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            free(buffer);

            if (character == EOF && ferror(stdin)) {
                return -1;
            }

            return 0;
        }

        if (used + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 16U : capacity * 2U;

            if (new_capacity > MAX_PASSWORD_LENGTH + 1U) {
                new_capacity = MAX_PASSWORD_LENGTH + 1U;
            }

            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (character == EOF && used == 0U) {
        free(buffer);
        return 0;
    }

    if (buffer == NULL) {
        buffer = malloc(1U);

        if (buffer == NULL) {
            return -1;
        }
    }

    buffer[used] = '\0';
    *password = buffer;
    *length = used;

    return 1;
}

int main(void)
{
    char *password = NULL;
    size_t length = 0U;
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