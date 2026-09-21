#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

enum {
    MINIMUM_PASSWORD_LENGTH = 8,
    MAXIMUM_PASSWORD_LENGTH = 128,
    PASSWORD_BUFFER_SIZE = MAXIMUM_PASSWORD_LENGTH + 2
};

static bool is_password_valid(const char *password, size_t length)
{
    bool has_lowercase = false;
    bool has_uppercase = false;
    bool has_digit = false;
    bool has_special = false;
    static const char special_characters[] = "!@#$%^&*()-_=+[]{};:,.?/";

    if (password == NULL ||
        length < MINIMUM_PASSWORD_LENGTH ||
        length > MAXIMUM_PASSWORD_LENGTH) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
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
        } else if (strchr(special_characters, character) != NULL) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_lowercase && has_uppercase && has_digit && has_special;
}

static bool consume_line_ending(bool *line_too_long)
{
    int character;

    if (line_too_long == NULL) {
        return false;
    }

    *line_too_long = false;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n') {
        if (character == EOF) {
            return !ferror(stdin);
        }

        *line_too_long = true;
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char password[PASSWORD_BUFFER_SIZE];

    if (fgets(password, (int)sizeof password, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(password, "\r\n");

    if (password[length] == '\n') {
        password[length] = '\0';
    } else if (password[length] == '\r') {
        password[length] = '\0';

        if (password[length + 1U] == '\n') {
            password[length + 1U] = '\0';
        } else if (password[length + 1U] == '\0') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int character = getchar();

            if (character != '\n' && character != EOF) {
                if (ungetc(character, stdin) == EOF) {
                    return 1;
                }
            } else if (character == EOF && ferror(stdin)) {
                return 1;
            }
        }
    } else if (length == sizeof password - 1U) {
        bool line_too_long;

        if (!consume_line_ending(&line_too_long)) {
            return 1;
        }

        if (line_too_long) {
            puts("false");
            return 0;
        }
    }

    puts(is_password_valid(password, length) ? "true" : "false");
    return 0;
}