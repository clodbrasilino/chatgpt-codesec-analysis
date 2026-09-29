#include <errno.h>
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

    if (email == NULL || length == 0 || length > MAX_EMAIL_LENGTH) {
        return false;
    }

    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    const int result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

static ReadStatus discard_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char discard[256];

    for (;;) {
        if (fgets(discard, sizeof discard, stdin) == NULL) {
            return ferror(stdin) ? READ_ERROR : READ_TOO_LONG;
        }

        size_t length = 0;
        while (discard[length] != '\0' && discard[length] != '\n') {
            ++length;
        }

        if (discard[length] == '\n') {
            return READ_TOO_LONG;
        }
    }
}

static ReadStatus read_line(char **line_out, size_t *length_out)
{
    if (line_out == NULL || length_out == NULL) {
        return READ_ERROR;
    }

    *line_out = NULL;
    *length_out = 0;

    const size_t capacity = MAX_EMAIL_LENGTH + 2U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return READ_ERROR;
    }

    errno = 0;
    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        ReadStatus status = ferror(stdin) ? READ_ERROR : READ_EOF;
        free(buffer);
        return status;
    }

    size_t length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (!feof(stdin)) {
        ReadStatus status = discard_line();
        free(buffer);
        return status;
    } else if (ferror(stdin)) {
        free(buffer);
        return READ_ERROR;
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