#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 254U

static bool is_valid_email(const char *email, size_t length)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?)+$";
    regex_t regex;
    int result;

    if (email == NULL || length == 0U || length > MAX_EMAIL_LENGTH ||
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        strlen(email) != length) {
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

static bool discard_remaining_line(FILE *stream)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    if (stream == NULL) {
        return false;
    }

    while (fgets(buffer, sizeof buffer, stream) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(buffer);

        if (length > 0U &&
            (buffer[length - 1U] == '\n' || buffer[length - 1U] == '\r')) {
            return true;
        }
    }

    return !ferror(stream);
}

static char *read_line(FILE *stream, size_t max_length, size_t *length_out)
{
    size_t capacity;
    size_t length;
    char *buffer;

    if (stream == NULL || length_out == NULL || max_length == SIZE_MAX) {
        return NULL;
    }

    *length_out = 0U;
    capacity = max_length + 1U;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    if (fgets(buffer, capacity, stream) == NULL) {
        free(buffer);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(buffer);

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[--length] = '\0';

        if (length > 0U && buffer[length - 1U] == '\r') {
            buffer[--length] = '\0';
        }
    } else if (length > 0U && buffer[length - 1U] == '\r') {
        buffer[--length] = '\0';
    } else if (length == max_length) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = fgetc(stream);

        if (next == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            next = fgetc(stream);
            if (next != '\n' && next != EOF && ungetc(next, stream) == EOF) {
                free(buffer);
                return NULL;
            }
        } else if (next != '\n' && next != EOF) {
            if (!discard_remaining_line(stream)) {
                free(buffer);
                return NULL;
            }
            free(buffer);
            return NULL;
        }

        if (next == EOF && ferror(stream)) {
            free(buffer);
            return NULL;
        }
    }

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