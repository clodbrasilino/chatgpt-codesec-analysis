#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int move_digits_to_end(char *str, size_t capacity)
{
    size_t length;
    size_t write_index = 0;
    char *result;

    if (str == NULL || capacity == 0) {
        return -1;
    }

    length = strnlen(str, capacity);
    if (length == capacity) {
        return -1;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!isdigit((unsigned char)str[i])) {
            result[write_index++] = str[i];
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (isdigit((unsigned char)str[i])) {
            result[write_index++] = str[i];
        }
    }

    result[write_index] = '\0';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, result, write_index + 1);
    free(result);

    return 0;
}

static int discard_line(FILE *stream)
{
    int ch;

    if (stream == NULL) {
        return -1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    } while (ch != '\n' && ch != EOF);

    return ferror(stream) ? -1 : 0;
}

int main(void)
{
    enum { INPUT_CAPACITY = 1024 };
    char *input;
    size_t length;

    input = malloc(INPUT_CAPACITY);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, INPUT_CAPACITY, stdin) == NULL) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(input);
        return status;
    }

    length = strnlen(input, INPUT_CAPACITY);
    if (length == INPUT_CAPACITY) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';

        if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        if (discard_line(stdin) != 0) {
            free(input);
            return EXIT_FAILURE;
        }

        free(input);
        return EXIT_FAILURE;
    }

    if (move_digits_to_end(input, INPUT_CAPACITY) != 0) {
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