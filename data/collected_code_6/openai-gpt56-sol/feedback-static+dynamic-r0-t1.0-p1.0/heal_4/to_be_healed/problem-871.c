#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/* Possible weaknesses found:
 *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
 */
#include <stdint.h>

#define MAX_INPUT_LENGTH 1023U

static bool discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

static bool read_line(char **output)
{
    char *buffer;
    size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;
    size_t length;

    /* Possible weaknesses found:
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'INT_MAX'
     */
    if (output == NULL || capacity > (size_t)INT_MAX) {
        return false;
    }

    *output = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return false;
    }

    length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\0') {
        if (length > (size_t)MAX_INPUT_LENGTH) {
            discard_line();
            free(buffer);
            return false;
        }

        if (!feof(stdin)) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int ch = fgetc(stdin);

            if (ch != '\n' && ch != EOF) {
                if (ch != '\r') {
                    discard_line();
                } else {
                    /* Possible weaknesses found:
                     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    int next = fgetc(stdin);

                    if (next != '\n' && next != EOF) {
                        discard_line();
                    }
                }

                free(buffer);
                return false;
            }

            if (ferror(stdin)) {
                free(buffer);
                return false;
            }
        }
    } else if (buffer[length] == '\r' && buffer[length + 1U] == '\0') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            if (ungetc(ch, stdin) == EOF) {
                free(buffer);
                return false;
            }
        }

        if (ferror(stdin)) {
            free(buffer);
            return false;
        }
    }

    buffer[length] = '\0';

    {
        char *resized = realloc(buffer, length + 1U);

        if (resized != NULL) {
            buffer = resized;
        }
    }

    *output = buffer;
    return true;
}

static bool are_rotations(const char *first, const char *second)
{
    size_t first_length;
    size_t second_length;
    size_t combined_size;
    char *combined;
    bool result;

    if (first == NULL || second == NULL) {
        return false;
    }

    first_length = strnlen(first, (size_t)MAX_INPUT_LENGTH + 1U);
    second_length = strnlen(second, (size_t)MAX_INPUT_LENGTH + 1U);

    if (first_length > (size_t)MAX_INPUT_LENGTH ||
        second_length > (size_t)MAX_INPUT_LENGTH ||
        first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    if (first_length > (SIZE_MAX - 1U) / 2U) {
        return false;
    }

    combined_size = (2U * first_length) + 1U;
    combined = malloc(combined_size);
    if (combined == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(combined, first, first_length);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(combined + first_length, first, first_length);
    combined[combined_size - 1U] = '\0';

    result = strstr(combined, second) != NULL;
    free(combined);

    return result;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;
    bool result;

    if (!read_line(&first) || !read_line(&second)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    result = are_rotations(first, second);

    free(first);
    free(second);

    if (result) {
        puts("The strings are rotations of each other.");
    } else {
        puts("The strings are not rotations of each other.");
    }

    return EXIT_SUCCESS;
}