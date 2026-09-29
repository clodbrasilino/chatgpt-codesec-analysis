#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void remove_odd_indices(char *string)
{
    size_t read_index = 0U;
    size_t write_index = 0U;

    if (string == NULL) {
        return;
    }

    while (string[read_index] != '\0') {
        string[write_index++] = string[read_index];

        if (string[read_index + 1U] == '\0') {
            break;
        }

        read_index += 2U;
    }

    string[write_index] = '\0';
}

int main(void)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *string = malloc(capacity);

    if (string == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                free(string);
                return EXIT_FAILURE;
            }
            break;
        }

        if (length >= SIZE_MAX - 1U) {
            free(string);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(string);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            resized = realloc(string, new_capacity);

            if (resized == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = resized;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)ch;
    }

    if (length == 0U && feof(stdin)) {
        free(string);
        return EXIT_FAILURE;
    }

    string[length] = '\0';
    remove_odd_indices(string);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}