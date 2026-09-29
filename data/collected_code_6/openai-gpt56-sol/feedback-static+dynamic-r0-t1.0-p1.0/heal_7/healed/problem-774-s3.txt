#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 254U
#define INPUT_BUFFER_SIZE (MAX_EMAIL_LENGTH + 2U)

static bool is_valid_email(const char *email, size_t length)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]([A-Za-z0-9-]{0,61}[A-Za-z0-9])?)+$";
    regex_t regex;
    int status;

    if (email == NULL || length == 0U || length > MAX_EMAIL_LENGTH) {
        return false;
    }

    if (email[length] != '\0' || memchr(email, '\0', length) != NULL) {
        return false;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return false;
    }

    status = regexec(&regex, email, 0U, NULL, 0);
    regfree(&regex);

    return status == 0;
}

static bool discard_line(FILE *stream)
{
    int ch;

    if (stream == NULL) {
        return false;
    }

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
    }

    return !ferror(stream);
}

static char *read_line(FILE *stream, size_t *length_out)
{
    char input[INPUT_BUFFER_SIZE];
    char *result;
    size_t length;
    bool terminated;

    if (stream == NULL || length_out == NULL) {
        return NULL;
    }

    *length_out = 0U;

    if (fgets(input, sizeof input, stream) == NULL) {
        return NULL;
    }

    length = strlen(input);
    terminated = false;

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';
        terminated = true;

        if (length > 0U && input[length - 1U] == '\r') {
            input[--length] = '\0';
        }
    } else if (length > 0U && input[length - 1U] == '\r') {
        input[--length] = '\0';
        terminated = true;
    }

    if (!terminated && !feof(stream)) {
        if (!discard_line(stream)) {
            return NULL;
        }
        return NULL;
    }

    if (length == 0U || length > MAX_EMAIL_LENGTH) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, input, length);
    result[length] = '\0';
    *length_out = length;

    return result;
}

int main(void)
{
    size_t length = 0U;
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