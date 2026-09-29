#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

enum {
    MINIMUM_PASSWORD_LENGTH = 8,
    MAXIMUM_PASSWORD_LENGTH = 128,
    PASSWORD_BUFFER_SIZE = MAXIMUM_PASSWORD_LENGTH + 2
};

static size_t bounded_string_length(const char *string, size_t maximum)
{
    size_t length = 0;

    while (length < maximum && string[length] != '\0') {
        ++length;
    }

    return length;
}

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

    length = bounded_string_length(password, MAXIMUM_PASSWORD_LENGTH + 1U);

    if (length < MINIMUM_PASSWORD_LENGTH ||
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

static bool discard_line_remainder(void)
{
    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();
    } while (character != '\n' && character != EOF);

    return character == '\n' || feof(stdin) != 0;
}

static bool read_password(char *buffer, size_t buffer_size)
{
    size_t length;

    if (buffer == NULL ||
        buffer_size < 2U ||
        buffer_size > PASSWORD_BUFFER_SIZE ||
        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MAX'
         */
        buffer_size > (size_t)INT_MAX) {
        return false;
    }

    buffer[0] = '\0';

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return false;
    }

    length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return true;
    }

    if (buffer[length] == '\r') {
        bool complete = buffer[length + 1U] == '\n';

        buffer[length] = '\0';

        if (complete || feof(stdin) != 0) {
            return true;
        }

        if (!discard_line_remainder()) {
            buffer[0] = '\0';
            return false;
        }

        return true;
    }

    if (feof(stdin) != 0) {
        return true;
    }

    if (!discard_line_remainder()) {
        buffer[0] = '\0';
        return false;
    }

    buffer[0] = '\0';
    return true;
}

int main(void)
{
    char *password = calloc(PASSWORD_BUFFER_SIZE, sizeof *password);
    int result = 1;

    if (password == NULL) {
        return 1;
    }

    if (read_password(password, PASSWORD_BUFFER_SIZE)) {
        puts(is_password_valid(password) ? "true" : "false");
        result = 0;
    }

    memset(password, 0, PASSWORD_BUFFER_SIZE);
    free(password);

    return result;
}