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

    return !ferror(stream);
}

static char *read_line(FILE *stream, size_t *length_out)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    char *result;
    size_t length = 0U;
    bool terminated = false;
    /* Possible weaknesses found:
     *  The scope of the variable 'next' can be reduced. [variableScope]
     */
    int next;

    if (stream == NULL || length_out == NULL) {
        return NULL;
    }

    *length_out = 0U;

    if (fgets(input, (int)sizeof input, stream) == NULL) {
        return NULL;
    }

    while (length < sizeof input && input[length] != '\0') {
        ++length;
    }

    if (length == sizeof input) {
        if (!discard_line(stream)) {
            return NULL;
        }
        return NULL;
    }

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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        next = fgetc(stream);

        if (next == '\n') {
            /* Possible weaknesses found:
             *  Variable 'terminated' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'terminated' is never read [deadcode.DeadStores]
             */
            terminated = true;
        } else if (next == EOF) {
            if (ferror(stream)) {
                return NULL;
            }
            /* Possible weaknesses found:
             *  Variable 'terminated' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'terminated' is never read [deadcode.DeadStores]
             */
            terminated = true;
        } else {
            if (!discard_line(stream)) {
                return NULL;
            }
            return NULL;
        }
    }

    if (length == 0U || length > MAX_EMAIL_LENGTH) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, input, length + 1U);
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

    puts(is_valid_email(email, length)
             ? "Valid email address"
             : "Invalid email address");

    free(email);
    return EXIT_SUCCESS;
}