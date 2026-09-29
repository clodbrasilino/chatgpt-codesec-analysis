#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    DATE_LENGTH = 10,
    OUTPUT_BUFFER_SIZE = DATE_LENGTH + 1
};

static int convert_date(const char *input, size_t input_length,
                        char *output, size_t output_size)
{
    if (input == NULL || output == NULL ||
        input_length != DATE_LENGTH ||
        output_size < OUTPUT_BUFFER_SIZE) {
        return -1;
    }

    if (input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (size_t i = 0; i < DATE_LENGTH; ++i) {
        if (i != 4 && i != 7 &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    int written = snprintf(output, output_size, "%.2s-%.2s-%.4s",
                           input + 8, input + 5, input);

    return written == DATE_LENGTH ? 0 : -1;
}

static int read_date(char **input, size_t *length)
{
    if (input == NULL || length == NULL) {
        return -1;
    }

    *input = NULL;
    *length = 0;

    size_t capacity = 16;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (*length > DATE_LENGTH) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            free(buffer);
            return 1;
        }

        if (*length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[(*length)++] = (char)ch;
    }

    if (ch == EOF && *length == 0) {
        free(buffer);
        return -1;
    }

    if (*length > 0 && buffer[*length - 1] == '\r') {
        --*length;
    }

    buffer[*length] = '\0';
    *input = buffer;

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[OUTPUT_BUFFER_SIZE];

    int read_result = read_date(&input, &length);

    if (read_result < 0) {
        fputs("Failed to read the date.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_result > 0) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (convert_date(input, length, output, sizeof output) != 0) {
        free(input);
        fputs("Invalid date format.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (puts(output) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}