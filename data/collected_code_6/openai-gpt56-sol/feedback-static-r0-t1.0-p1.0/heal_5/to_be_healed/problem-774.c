#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_EMAIL_LENGTH = 320 };

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

static bool discard_until_newline(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n') {
        if (ch == EOF) {
            return !ferror(stdin);
        }
    }

    return true;
}

static char *read_line(size_t max_length, size_t *length_out)
{
    if (length_out == NULL || max_length == 0 || max_length == SIZE_MAX) {
        return NULL;
    }

    char *line = malloc(max_length + 1);
    if (line == NULL) {
        return NULL;
    }

    size_t length = 0;
    int ch = EOF;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (length < max_length && (ch = getchar()) != '\n' && ch != EOF) {
        line[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(line);
        return NULL;
    }

    if (length == max_length) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch != '\n' && ch != EOF) {
            if (!discard_until_newline()) {
                free(line);
                return NULL;
            }

            free(line);
            return NULL;
        }

        if (ch == EOF && ferror(stdin)) {
            free(line);
            return NULL;
        }
    }

    if (length > 0 && line[length - 1] == '\r') {
        --length;
    }

    line[length] = '\0';
    *length_out = length;

    return line;
}

int main(void)
{
    size_t length = 0;
    char *email = read_line(MAX_EMAIL_LENGTH, &length);

    if (email == NULL) {
        return EXIT_FAILURE;
    }

    puts(is_valid_email(email, length) ? "Valid" : "Invalid");
    free(email);

    return EXIT_SUCCESS;
}