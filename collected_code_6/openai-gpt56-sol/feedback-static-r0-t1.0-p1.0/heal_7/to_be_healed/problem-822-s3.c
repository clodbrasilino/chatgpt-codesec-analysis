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
        } else if (strchr(special_characters, (int)character) != NULL) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_lowercase && has_uppercase && has_digit && has_special;
}

static bool discard_until_newline(void)
{
    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    return character == '\n' || !ferror(stdin);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char password[PASSWORD_BUFFER_SIZE];

    if (fgets(password, sizeof password, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(password, "\r\n");

    if (password[length] == '\r' || password[length] == '\n') {
        char terminator = password[length];
        password[length] = '\0';

        if (terminator == '\r' && password[length + 1U] == '\0') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int character = fgetc(stdin);

            if (character != '\n' && character != EOF) {
                if (ungetc(character, stdin) == EOF) {
                    return 1;
                }
            } else if (character == EOF && ferror(stdin)) {
                return 1;
            }
        }
    } else if (password[length] == '\0' &&
               length == sizeof password - 1U) {
        if (!discard_until_newline()) {
            return 1;
        }

        puts("false");
        return 0;
    }

    puts(is_password_valid(password, length) ? "true" : "false");
    return 0;
}