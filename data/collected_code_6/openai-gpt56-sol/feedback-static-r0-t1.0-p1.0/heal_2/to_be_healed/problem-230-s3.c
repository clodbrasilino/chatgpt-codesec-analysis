#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LIMIT 1024U

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        char *resized;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return NULL;
        }

        if (length >= INPUT_LIMIT) {
            while (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stream);
            }
            free(buffer);
            return NULL;
        }

        if (length + 1U >= capacity) {
            new_capacity = capacity == 0U ? 64U : capacity * 2U;

            if (new_capacity > INPUT_LIMIT + 1U) {
                new_capacity = INPUT_LIMIT + 1U;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        free(buffer);
        return NULL;
    }

    if (buffer == NULL) {
        buffer = malloc(1U);
        if (buffer == NULL) {
            return NULL;
        }
    }

    buffer[length] = '\0';
    return buffer;
}

static char *replace_spaces(const char *source, size_t length, char replacement)
{
    char *result;
    size_t i;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < length; ++i) {
        result[i] = source[i] == ' ' ? replacement : source[i];
    }

    result[length] = '\0';
    return result;
}

int main(void)
{
    char *input;
    char *result;
    int replacement;
    size_t length;

    input = read_line(stdin);
    if (input == NULL) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        replacement = fgetc(stdin);
    } while (replacement != EOF &&
             (replacement == ' ' || replacement == '\t' ||
              replacement == '\n' || replacement == '\r' ||
              replacement == '\f' || replacement == '\v'));

    if (replacement == EOF) {
        fputs("Failed to read the replacement character.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input);
    result = replace_spaces(input, length, (char)replacement);
    free(input);

    if (result == NULL) {
        fputs("Failed to replace spaces.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}