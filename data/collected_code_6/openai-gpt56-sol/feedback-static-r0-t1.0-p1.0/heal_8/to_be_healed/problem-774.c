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

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    if (ch == EOF && ferror(stdin)) {
        return READ_ERROR;
    }

    return READ_TOO_LONG;
}

static ReadStatus read_line(char **line_out, size_t *length_out)
{
    const size_t capacity = MAX_EMAIL_LENGTH + 2U;
    char *buffer;
    size_t length = 0;

    if (line_out == NULL || length_out == NULL) {
        return READ_ERROR;
    }

    *line_out = NULL;
    *length_out = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return READ_ERROR;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        ReadStatus status = ferror(stdin) ? READ_ERROR : READ_EOF;
        free(buffer);
        return status;
    }

    while (length < capacity && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length < capacity && buffer[length] == '\n') {
        buffer[length] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n') {
            free(buffer);
            return READ_TOO_LONG;
        }

        if (ch != EOF) {
            ReadStatus status = discard_line();
            free(buffer);
            return status;
        }

        if (ferror(stdin)) {
            free(buffer);
            return READ_ERROR;
        }
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        buffer[--length] = '\0';
    }

    if (length > MAX_EMAIL_LENGTH) {
        free(buffer);
        return READ_TOO_LONG;
    }

    *line_out = buffer;
    *length_out = length;
    return READ_OK;
}

int main(void)
{
    char *email = NULL;
    size_t length = 0;
    ReadStatus status = read_line(&email, &length);

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