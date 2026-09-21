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
    int result;

    if (email == NULL || length == 0 || length > MAX_EMAIL_LENGTH) {
        return false;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return false;
    }

    result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

static ReadStatus discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    if (ch == EOF && ferror(stdin)) {
        return READ_ERROR;
    }

    return READ_TOO_LONG;
}

static ReadStatus read_line(char **line_out, size_t *length_out)
{
    char *buffer;
    size_t length;
    int ch;

    if (line_out == NULL || length_out == NULL) {
        return READ_ERROR;
    }

    *line_out = NULL;
    *length_out = 0;

    buffer = malloc((size_t)MAX_EMAIL_LENGTH + 1U);
    if (buffer == NULL) {
        return READ_ERROR;
    }

    length = 0;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return READ_ERROR;
            }

            if (length == 0) {
                free(buffer);
                return READ_EOF;
            }

            break;
        }

        if (length == MAX_EMAIL_LENGTH) {
            ReadStatus status;

            free(buffer);
            status = discard_line();
            return status;
        }

        buffer[length] = (char)ch;
        ++length;
    }

    if (length > 0 && buffer[length - 1U] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line_out = buffer;
    *length_out = length;

    return READ_OK;
}

int main(void)
{
    char *email;
    size_t length;
    ReadStatus status;

    email = NULL;
    length = 0;
    status = read_line(&email, &length);

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