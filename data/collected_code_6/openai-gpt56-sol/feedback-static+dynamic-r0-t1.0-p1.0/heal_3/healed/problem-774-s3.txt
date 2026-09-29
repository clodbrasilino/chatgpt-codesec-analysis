#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EMAIL_LENGTH 254

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

    status = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return false;
    }

    status = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return status == 0;
}

static bool discard_line(FILE *stream, int ch)
{
    while (ch != EOF && ch != '\n' && ch != '\r') {
        ch = fgetc(stream);
    }

    if (ch == '\r') {
        int next = fgetc(stream);

        if (next != '\n' && next != EOF && ungetc(next, stream) == EOF) {
            return false;
        }
    }

    return !ferror(stream);
}

static char *read_line(FILE *stream, size_t *length_out)
{
    char *buffer;
    size_t length = 0;
    int ch;

    if (stream == NULL || length_out == NULL) {
        return NULL;
    }

    *length_out = 0;
    buffer = malloc(MAX_EMAIL_LENGTH + 1);
    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next != '\n' && next != EOF && ungetc(next, stream) == EOF) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length == MAX_EMAIL_LENGTH) {
            if (!discard_line(stream, ch)) {
                free(buffer);
                return NULL;
            }

            free(buffer);
            return NULL;
        }

        buffer[length++] = (char)ch;
    }

    if (ferror(stream) || (ch == EOF && length == 0)) {
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