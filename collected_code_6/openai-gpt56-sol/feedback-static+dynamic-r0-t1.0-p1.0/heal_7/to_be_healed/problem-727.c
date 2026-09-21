#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int remove_non_alphanumeric(const char *input, size_t input_len, char **output)
{
    char *result;
    size_t read_pos;
    size_t write_pos = 0;

    if (output == NULL) {
        return -1;
    }

    *output = NULL;

    if ((input == NULL && input_len != 0) || input_len == SIZE_MAX) {
        return -1;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        unsigned char ch = (unsigned char)input[read_pos];

        if ((ch >= (unsigned char)'0' && ch <= (unsigned char)'9') ||
            (ch >= (unsigned char)'A' && ch <= (unsigned char)'Z') ||
            (ch >= (unsigned char)'a' && ch <= (unsigned char)'z')) {
            result[write_pos++] = (char)ch;
        }
    }

    result[write_pos] = '\0';
    *output = result;

    return 0;
}

int main(void)
{
    enum { INPUT_BUFFER_SIZE = 4096 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    char *output = NULL;
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n' && input[length] != '\r') {
        ++length;
    }

    if (length == sizeof input) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Redundant condition: The condition 'input[length] != '\r'' is redundant since 'input[length] == '\0'' is sufficient. [redundantCondition]
     */
    if (input[length] != '\n' && input[length] != '\r' &&
        input[length] == '\0' && !feof(stdin)) {
        int ch;

        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (remove_non_alphanumeric(input, length, &output) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}