#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EMAIL_LENGTH 254U

static bool is_valid_email(const char *email, size_t length)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?)+$";
    regex_t regex;
    bool valid;

    if (email == NULL || length == 0U || length > MAX_EMAIL_LENGTH) {
        return false;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    valid = regexec(&regex, email, 0, NULL, 0) == 0;
    regfree(&regex);

    return valid;
}

static bool discard_line(FILE *stream)
{
    int ch;

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
    }

    return ch == '\n' || !ferror(stream);
}

static char *read_line(FILE *stream, size_t max_length, size_t *length_out)
{
    size_t capacity;
    size_t length = 0U;
    char *buffer;
    int ch = EOF;

    if (stream == NULL || length_out == NULL || max_length == SIZE_MAX) {
        return NULL;
    }

    *length_out = 0U;
    capacity = max_length + 1U;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF) {
        if (ch == '\n' || ch == '\r') {
            break;
        }

        if (length >= max_length) {
            if (!discard_line(stream)) {
                clearerr(stream);
            }
            free(buffer);
            return NULL;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stream) || length == 0U) {
            free(buffer);
            return NULL;
        }
    } else if (ch == '\r') {
        int next = fgetc(stream);

        if (next != '\n' && next != EOF) {
            if (ungetc(next, stream) == EOF) {
                free(buffer);
                return NULL;
            }
        } else if (next == EOF && ferror(stream)) {
            free(buffer);
            return NULL;
        }
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