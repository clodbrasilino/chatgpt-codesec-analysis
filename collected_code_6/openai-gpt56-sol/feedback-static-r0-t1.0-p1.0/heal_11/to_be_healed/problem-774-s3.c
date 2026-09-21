#include <limits.h>
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

    if (email == NULL ||
        length == 0U ||
        length > MAX_EMAIL_LENGTH ||
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

static bool discard_until_line_end(FILE *stream)
{
    int character;

    if (stream == NULL) {
        return false;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);
    } while (character != '\n' && character != EOF);

    return character == '\n' || !ferror(stream);
}

static char *read_line(FILE *stream, size_t max_length, size_t *length_out)
{
    char *buffer;
    size_t length = 0U;
    int character;

    if (stream == NULL ||
        length_out == NULL ||
        max_length == 0U ||
        max_length > SIZE_MAX - 1U) {
        return NULL;
    }

    *length_out = 0U;
    buffer = malloc(max_length + 1U);

    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        if (character == '\n') {
            buffer[length] = '\0';
            *length_out = length;
            return buffer;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int following = fgetc(stream);

            if (following != '\n' && following != EOF) {
                if (ungetc(following, stream) == EOF) {
                    free(buffer);
                    return NULL;
                }
            } else if (following == EOF && ferror(stream)) {
                free(buffer);
                return NULL;
            }

            buffer[length] = '\0';
            *length_out = length;
            return buffer;
        }

        if (length == max_length) {
            if (!discard_until_line_end(stream)) {
                free(buffer);
                return NULL;
            }

            free(buffer);
            return NULL;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stream) || length == 0U) {
        free(buffer);
        return NULL;
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