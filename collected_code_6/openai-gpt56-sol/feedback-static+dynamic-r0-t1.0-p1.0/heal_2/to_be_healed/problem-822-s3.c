#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum {
    MINIMUM_PASSWORD_LENGTH = 8,
    MAXIMUM_PASSWORD_LENGTH = 128,
    PASSWORD_BUFFER_SIZE = MAXIMUM_PASSWORD_LENGTH + 2
};

static bool is_password_valid(const char *password)
{
    static const char special_characters[] = "!@#$%^&*()-_=+[]{};:,.?/";
    bool has_lowercase = false;
    bool has_uppercase = false;
    bool has_digit = false;
    bool has_special = false;
    size_t length = 0U;

    if (password == NULL) {
        return false;
    }

    while (length <= MAXIMUM_PASSWORD_LENGTH && password[length] != '\0') {
        unsigned char character = (unsigned char)password[length];

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

        ++length;
    }

    if (length > MAXIMUM_PASSWORD_LENGTH) {
        return false;
    }

    return length >= MINIMUM_PASSWORD_LENGTH &&
           has_lowercase &&
           has_uppercase &&
           has_digit &&
           has_special;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char password[PASSWORD_BUFFER_SIZE];
    size_t length;

    if (fgets(password, sizeof password, stdin) == NULL) {
        return 1;
    }

    length = strcspn(password, "\r\n");

    if (password[length] != '\0') {
        password[length] = '\0';
    } else if (length == sizeof password - 1U) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = getchar();
        } while (character != '\n' && character != EOF);

        puts("false");
        return 0;
    }

    puts(is_password_valid(password) ? "true" : "false");
    return 0;
}