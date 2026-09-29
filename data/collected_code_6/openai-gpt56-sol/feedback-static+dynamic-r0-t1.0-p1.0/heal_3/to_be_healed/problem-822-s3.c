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
    size_t length;

    if (password == NULL) {
        return false;
    }

    for (length = 0; length <= MAXIMUM_PASSWORD_LENGTH; ++length) {
        unsigned char character = (unsigned char)password[length];

        if (character == '\0') {
            break;
        }

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

    return length >= MINIMUM_PASSWORD_LENGTH &&
           length <= MAXIMUM_PASSWORD_LENGTH &&
           has_lowercase &&
           has_uppercase &&
           has_digit &&
           has_special;
}

static bool discard_line(void)
{
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
    }

    return character == '\n';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char password[PASSWORD_BUFFER_SIZE];
    size_t length;

    if (fgets(password, (int)sizeof password, stdin) == NULL) {
        return 1;
    }

    length = strcspn(password, "\r\n");

    if (password[length] != '\0') {
        password[length] = '\0';
    } else if (!feof(stdin)) {
        discard_line();
        puts("false");
        return 0;
    }

    puts(is_password_valid(password) ? "true" : "false");
    return 0;
}