#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

#define MAX_INPUT_LENGTH 1023U

static bool read_line(char **line)
{
    if (line == NULL) {
        return false;
    }

    size_t capacity = 128U;
    size_t length = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return false;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0U) {
                free(buffer);
                return false;
            }
            break;
        }

        if (length >= MAX_INPUT_LENGTH) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            free(buffer);
            return false;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity = capacity * 2U;

            if (new_capacity > MAX_INPUT_LENGTH + 1U) {
                new_capacity = MAX_INPUT_LENGTH + 1U;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return false;
            }

            char *resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return true;
}

static bool are_rotations(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t first_length = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    if (first_length > (SIZE_MAX - 1U) / 2U) {
        return false;
    }

    size_t doubled_length = first_length * 2U;
    char *doubled = malloc(doubled_length + 1U);

    if (doubled == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(doubled, first, first_length);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(doubled + first_length, first, first_length);
    doubled[doubled_length] = '\0';

    bool result = strstr(doubled, second) != NULL;

    free(doubled);
    return result;
}

int main(void)
{
    char *first = NULL;
    char *second = NULL;

    if (!read_line(&first) || !read_line(&second)) {
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    bool result = are_rotations(first, second);

    free(first);
    free(second);

    if (puts(result ? "Yes" : "No") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}