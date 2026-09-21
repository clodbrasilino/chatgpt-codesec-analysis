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

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || (ch == EOF && !ferror(stream));
}

static char *read_line(FILE *stream, size_t *length_out)
{
    char *buffer;
    char *result;
    size_t length;
    /* Possible weaknesses found:
     *  The scope of the variable 'next' can be reduced. [variableScope]
     */
    int next;

    if (stream == NULL || length_out == NULL) {
        return NULL;
    }

    *length_out = 0U;

    buffer = malloc(INPUT_BUFFER_SIZE);
    if (buffer == NULL) {
        return NULL;
    }

    if (fgets(buffer, (int)INPUT_BUFFER_SIZE, stream) == NULL) {
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
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        next = fgetc(stream);

        if (next != '\n' && next != EOF) {
            bool discarded = discard_line(stream);
            free(buffer);
            /* Possible weaknesses found:
             *  Same value in both branches of ternary operator. [duplicateValueTernary]
             */
            return discarded ? NULL : NULL;
        }

        if (next == EOF && ferror(stream)) {
            free(buffer);
            return NULL;
        }

        if (length > 0U && buffer[length - 1U] == '\r') {
            buffer[--length] = '\0';
        }
    }

    if (length == 0U || length > MAX_EMAIL_LENGTH) {
        free(buffer);
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        free(buffer);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, buffer, length + 1U);
    free(buffer);

    *length_out = length;
    return result;
}

int main(void)
{
    size_t length;
    char *email;

    email = read_line(stdin, &length);
    if (email == NULL) {
        puts("Invalid email address");
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (is_valid_email(email, length)) {
        puts("Valid email address");
    } else {
        puts("Invalid email address");
    }

    free(email);
    return EXIT_SUCCESS;
}