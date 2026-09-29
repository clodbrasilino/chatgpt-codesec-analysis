#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EMAIL_LENGTH 254U

static size_t bounded_strlen(const char *string, size_t limit)
{
    size_t length = 0U;

    if (string == NULL) {
        return 0U;
    }

    while (length < limit && string[length] != '\0') {
        ++length;
    }

    return length;
}

static bool is_valid_email(const char *email, size_t length)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?)+$";
    regex_t regex;
    int result;

    if (email == NULL || length == 0U || length > MAX_EMAIL_LENGTH ||
        bounded_strlen(email, length + 1U) != length) {
        return false;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }

    result = regexec(&regex, email, 0U, NULL, 0);
    regfree(&regex);

    return result == 0;
}

static bool consume_line_ending(FILE *stream)
{
    int character;

    if (stream == NULL) {
        return false;
    }

    character = fgetc(stream);
    if (character == EOF) {
        return !ferror(stream);
    }

    if (character != '\n' && ungetc(character, stream) == EOF) {
        return false;
    }

    return true;
}

static bool discard_remaining_line(FILE *stream)
{
    if (stream == NULL) {
        return false;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            return !ferror(stream);
        }

        if (character == '\n') {
            return true;
        }

        if (character == '\r') {
            return consume_line_ending(stream);
        }
    }
}

static char *read_line(FILE *stream, size_t max_length, size_t *length_out)
{
    char *buffer;
    size_t length = 0U;

    if (stream == NULL || length_out == NULL || max_length == SIZE_MAX) {
        return NULL;
    }

    *length_out = 0U;
    buffer = malloc(max_length + 1U);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream) || length == 0U) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            if (!consume_line_ending(stream)) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length == max_length) {
            if (!discard_remaining_line(stream)) {
                free(buffer);
                return NULL;
            }

            free(buffer);
            return NULL;
        }

        buffer[length++] = (char)character;
    }

    buffer[length] = '\0';
    *length_out = length;
    return buffer;
}

int main(void)
{
    size_t length;
    char *email = read_line(stdin, MAX_EMAIL_LENGTH, &length);

    if (email == NULL) {
        return EXIT_FAILURE;
    }

    puts(is_valid_email(email, length)
             ? "Valid email address"
             : "Invalid email address");

    free(email);
    return EXIT_SUCCESS;
}