#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int string_to_lower(char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (unsigned char *p = (unsigned char *)string; *p != '\0'; ++p) {
        *p = (unsigned char)tolower((int)*p);
    }

    return 0;
}

int main(void)
{
    char *string = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (length > SIZE_MAX - 2) {
            free(string);
            return EXIT_FAILURE;
        }

        size_t required = length + 2;

        if (capacity < required) {
            size_t new_capacity = capacity == 0 ? 128 : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *new_string = realloc(string, new_capacity);
            if (new_string == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = new_string;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(string);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        free(string);
        return EXIT_SUCCESS;
    }

    string[length] = '\0';

    if (string_to_lower(string) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (fputs(string, stdout) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}