#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

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
        unsigned char character = (unsigned char)password[i];

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

static int read_password(char *password, size_t capacity, size_t *length)
{
    size_t used = 0;
    int character;

    if (password == NULL || length == NULL || capacity == 0U) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (used + 1U >= capacity) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }

            if (character == EOF && ferror(stdin)) {
                return -1;
            }

            password[0] = '\0';
            *length = 0U;
            return 0;
        }

        password[used++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        return -1;
    }

    if (used > 0U && password[used - 1U] == '\r') {
        --used;
    }

    password[used] = '\0';
    *length = used;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char password[MAX_PASSWORD_LENGTH + 1U];
    size_t length = 0U;
    int result = read_password(password, sizeof password, &length);

    if (result < 0) {
        return 1;
    }

    if (result == 0) {
        puts("false");
        return 0;
    }

    puts(is_valid_password(password, length) ? "true" : "false");
    return 0;
}