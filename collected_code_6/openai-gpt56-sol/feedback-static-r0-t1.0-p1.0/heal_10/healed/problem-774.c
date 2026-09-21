#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_EMAIL_LENGTH = 320 };

typedef enum {
    READ_OK,
    READ_TOO_LONG,
    READ_EOF,
    READ_ERROR
} ReadStatus;

static bool is_valid_email(const char *email, size_t length)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]([A-Za-z0-9-]*[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]([A-Za-z0-9-]*[A-Za-z0-9])?)+$";
    regex_t regex;

    if (email == NULL || length == 0U || length > MAX_EMAIL_LENGTH) {
        return false;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    const int result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

static ReadStatus discard_line(void)
{
    for (;;) {
        const int ch = fgetc(stdin);

        if (ch == '\n') {
            return READ_TOO_LONG;
        }

        if (ch == EOF) {
            return ferror(stdin) ? READ_ERROR : READ_TOO_LONG;
        }
    }
}

static ReadStatus read_line(char **line_out, size_t *length_out)
{
    char *buffer;
    size_t length = 0U;

    if (line_out == NULL || length_out == NULL) {
        return READ_ERROR;
    }

    *line_out = NULL;
    *length_out = 0U;

    buffer = malloc((size_t)MAX_EMAIL_LENGTH + 1U);
    if (buffer == NULL) {
        return READ_ERROR;
    }

    for (;;) {
        const int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return READ_ERROR;
            }

            if (length == 0U) {
                free(buffer);
                return READ_EOF;
            }

            break;
        }

        if (length >= (size_t)MAX_EMAIL_LENGTH) {
            free(buffer);
            return discard_line();
        }

        buffer[length++] = (char)ch;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line_out = buffer;
    *length_out = length;

    return READ_OK;
}

int main(void)
{
    char *email = NULL;
    size_t length = 0U;
    const ReadStatus status = read_line(&email, &length);

    if (status == READ_TOO_LONG) {
        puts("Invalid");
        return EXIT_SUCCESS;
    }

    if (status != READ_OK) {
        free(email);
        return EXIT_FAILURE;
    }

    puts(is_valid_email(email, length) ? "Valid" : "Invalid");
    free(email);

    return EXIT_SUCCESS;
}