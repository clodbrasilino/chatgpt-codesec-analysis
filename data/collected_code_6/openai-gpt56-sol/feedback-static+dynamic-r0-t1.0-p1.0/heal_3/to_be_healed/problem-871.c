#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 1023U

static bool read_line(char **output)
{
    char *buffer;
    size_t length;

    if (output == NULL) {
        return false;
    }

    *output = NULL;
    buffer = malloc(MAX_INPUT_LENGTH + 2U);
    if (buffer == NULL) {
        return false;
    }

    if (fgets(buffer, (int)(MAX_INPUT_LENGTH + 2U), stdin) == NULL) {
        free(buffer);
        return false;
    }

    length = strcspn(buffer, "\r\n");

    if (buffer[length] == '\0' && length > MAX_INPUT_LENGTH) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        free(buffer);
        return false;
    }

    if (buffer[length] == '\r') {
        if (buffer[length + 1U] == '\n') {
            buffer[length + 1U] = '\0';
        } else {
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
    char *combined;
    bool result;

    if (first == NULL || second == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    first_length = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    combined = malloc((2U * first_length) + 1U);
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
    combined[2U * first_length] = '\0';

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