#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

#define INPUT_SIZE 1024U

static int replace_spaces(char *string, size_t length, char replacement)
{
    size_t i;

    if (string == NULL || replacement == '\0') {
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        if (string[i] == ' ') {
            string[i] = replacement;
        }
    }

    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
}

static int read_line(char *buffer, size_t capacity, size_t *length)
{
    char *newline;
    size_t used;

    if (buffer == NULL || length == NULL || capacity < 2U ||
        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MAX'
         */
        capacity > (size_t)INT_MAX) {
        return -1;
    }

    buffer[0] = '\0';
    *length = 0U;

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
        *length = (size_t)(newline - buffer);
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    used = strlen(buffer);

    if (used == capacity - 1U) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            if (discard_line() != 0) {
                return -1;
            }

            buffer[0] = '\0';
            return -1;
        }

        if (ch == EOF && ferror(stdin)) {
            buffer[0] = '\0';
            return -1;
        }
    }

    *length = used;
    return 0;
}

static int read_replacement(char *replacement)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[3];
    size_t length;

    if (replacement == NULL) {
        return -1;
    }

    if (read_line(line, sizeof line, &length) != 0 ||
        length != 1U || line[0] == '\0') {
        return -1;
    }

    *replacement = line[0];
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    char replacement;
    size_t length;

    if (read_line(input, sizeof input, &length) != 0) {
        return EXIT_FAILURE;
    }

    if (read_replacement(&replacement) != 0) {
        return EXIT_FAILURE;
    }

    if (replace_spaces(input, length, replacement) != 0) {
        return EXIT_FAILURE;
    }

    if (fwrite(input, 1U, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}