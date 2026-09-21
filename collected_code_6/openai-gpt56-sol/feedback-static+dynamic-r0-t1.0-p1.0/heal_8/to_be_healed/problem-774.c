#include <limits.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAX_EMAIL_LENGTH = 320
};

static bool is_valid_email(const char *email)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]([A-Za-z0-9-]*[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]([A-Za-z0-9-]*[A-Za-z0-9])?)+$";
    regex_t regex;
    int result;

    if (email == NULL || email[0] == '\0') {
        return false;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

static bool discard_line(FILE *stream)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (stream == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == '\n') {
            return true;
        }

        if (ch == EOF) {
            return feof(stream) != 0;
        }
    }
}

static bool read_email(char **email)
{
    const size_t capacity = (size_t)MAX_EMAIL_LENGTH + 2U;
    char *buffer;
    size_t length;

    if (email == NULL || capacity > (size_t)INT_MAX) {
        return false;
    }

    *email = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return false;
    }

    length = strcspn(buffer, "\n");

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (!feof(stdin)) {
        if (!discard_line(stdin) && ferror(stdin)) {
            clearerr(stdin);
        }
        free(buffer);
        return false;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        buffer[--length] = '\0';
    }

    if (length == 0U || length > (size_t)MAX_EMAIL_LENGTH) {
        free(buffer);
        return false;
    }

    *email = buffer;
    return true;
}

int main(void)
{
    char *email = NULL;
    bool valid;

    if (!read_email(&email)) {
        return EXIT_FAILURE;
    }

    valid = is_valid_email(email);
    free(email);

    if (puts(valid ? "Valid" : "Invalid") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}