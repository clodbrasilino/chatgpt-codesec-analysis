#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
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

    if (email == NULL || length == 0 || length > MAX_EMAIL_LENGTH) {
        return false;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    int result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

static ReadStatus read_line(char *buffer, size_t capacity, size_t *length_out)
{
    if (buffer == NULL || length_out == NULL || capacity < 2) {
        return READ_ERROR;
    }

    *length_out = 0;

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return ferror(stdin) ? READ_ERROR : READ_EOF;
    }

    size_t length = 0;
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

        if (ch != '\n' && ch != EOF) {
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

        if (ch == EOF && ferror(stdin)) {
            return READ_ERROR;
        }
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        buffer[--length] = '\0';
    }

    *length_out = length;
    return READ_OK;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char email[MAX_EMAIL_LENGTH + 2];
    size_t length = 0;
    ReadStatus status = read_line(email, sizeof email, &length);

    if (status == READ_TOO_LONG) {
        puts("Invalid");
        return EXIT_SUCCESS;
    }

    if (status != READ_OK) {
        return EXIT_FAILURE;
    }

    puts(is_valid_email(email, length) ? "Valid" : "Invalid");
    return EXIT_SUCCESS;
}