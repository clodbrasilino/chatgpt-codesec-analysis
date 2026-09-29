#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int move_numbers_to_end(char *str, size_t capacity)
{
    size_t length;
    size_t position = 0;
    char *result;

    if (str == NULL || capacity == 0) {
        return -1;
    }

    length = strnlen(str, capacity);
    if (length == capacity || length == SIZE_MAX) {
        return -1;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!isdigit((unsigned char)str[i])) {
            result[position++] = str[i];
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (isdigit((unsigned char)str[i])) {
            result[position++] = str[i];
        }
    }

    result[position] = '\0';

    if (position >= capacity) {
        free(result);
        return -1;
    }

    for (size_t i = 0; i <= position; ++i) {
        str[i] = result[i];
    }

    free(result);
    return 0;
}

int main(void)
{
    size_t capacity = 1024;
    char *input = malloc(capacity);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)capacity, stdin) == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    size_t length = strnlen(input, capacity);
    if (length == capacity) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (length == capacity - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();
        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (move_numbers_to_end(input, capacity) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}