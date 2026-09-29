#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 254
#define INPUT_BUFFER_SIZE (MAX_EMAIL_LENGTH + 2)

static bool is_valid_email(const char *email, size_t length)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?)+$";
    regex_t regex;
    int status;

    if (email == NULL || length == 0 || length > MAX_EMAIL_LENGTH) {
        return false;
    }

    if (strlen(email) != length) {
        return false;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return false;
    }

    status = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return status == 0;
}

static bool discard_line(FILE *stream)
{
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stream) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return true;
        }

        {
            char *cr = strchr(buffer, '\r');

            if (cr != NULL) {
                size_t position = (size_t)(cr - buffer);

                if (cr[1] == '\0') {
                    int next = fgetc(stream);

                    if (next != '\n' && next != EOF &&
                        ungetc(next, stream) == EOF) {
                        return false;
                    }
                } else if (position + 1 < sizeof buffer &&
                           cr[1] != '\n') {
                    return false;
                }

                return !ferror(stream);
            }
        }
    }

    return !ferror(stream);
}

static char *read_line(FILE *stream, size_t *length_out)
{
    char input[INPUT_BUFFER_SIZE];
    char *newline;
    char *carriage_return;
    char *terminator;
    char *result;
    size_t length;

    if (stream == NULL || length_out == NULL) {
        return NULL;
    }

    *length_out = 0;

    if (fgets(input, sizeof input, stream) == NULL) {
        return NULL;
    }

    newline = strchr(input, '\n');
    carriage_return = strchr(input, '\r');
    terminator = newline;

    if (carriage_return != NULL &&
        (terminator == NULL || carriage_return < terminator)) {
        terminator = carriage_return;
    }

    if (terminator != NULL) {
        if (*terminator == '\r' && terminator[1] == '\0') {
            int next = fgetc(stream);

            if (next != '\n' && next != EOF &&
                ungetc(next, stream) == EOF) {
                return NULL;
            }
        }

        *terminator = '\0';
    } else {
        length = strlen(input);

        if (length == sizeof input - 1) {
            if (!discard_line(stream)) {
                return NULL;
            }
            return NULL;
        }
    }

    length = strlen(input);

    if (length == 0 || length > MAX_EMAIL_LENGTH) {
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, input, length + 1);
    *length_out = length;
    return result;
}

int main(void)
{
    size_t length;
    char *email = read_line(stdin, &length);

    if (email == NULL) {
        puts("Invalid email address");
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    puts(is_valid_email(email, length)
             ? "Valid email address"
             : "Invalid email address");

    free(email);
    return EXIT_SUCCESS;
}