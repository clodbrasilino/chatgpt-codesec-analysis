#include <stdio.h>
#include <stdlib.h>

#define DATE_TEXT_LENGTH 10U
#define DATE_BUFFER_SIZE (DATE_TEXT_LENGTH + 1U)

static int convert_date(const char *input, size_t input_length,
                        char *output, size_t output_size)
{
    size_t i;
    int result;

    if (input == NULL || output == NULL ||
        input_length != DATE_TEXT_LENGTH ||
        output_size < DATE_BUFFER_SIZE ||
        input[4] != '-' || input[7] != '-') {
        return -1;
    }

    for (i = 0U; i < DATE_TEXT_LENGTH; ++i) {
        if (i != 4U && i != 7U &&
            (input[i] < '0' || input[i] > '9')) {
            return -1;
        }
    }

    result = snprintf(output, output_size, "%c%c-%c%c-%c%c%c%c",
                      input[8], input[9],
                      input[5], input[6],
                      input[0], input[1], input[2], input[3]);

    if (result < 0 || (size_t)result >= output_size ||
        (size_t)result != DATE_TEXT_LENGTH) {
        return -1;
    }

    return 0;
}

static int read_date(char *buffer, size_t capacity, size_t *length)
{
    char *newline;
    size_t used;
    int ch;

    if (buffer == NULL || length == NULL ||
        capacity < DATE_BUFFER_SIZE) {
        return -1;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    newline = NULL;
    for (used = 0U; buffer[used] != '\0'; ++used) {
        if (buffer[used] == '\n' || buffer[used] == '\r') {
            newline = &buffer[used];
            break;
        }
    }

    if (newline != NULL) {
        char terminator = *newline;

        *newline = '\0';
        used = (size_t)(newline - buffer);

        if (terminator == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);
            if (ch != '\n' && ch != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
                }
                if (ferror(stdin)) {
                    return -1;
                }
                return 1;
            }
        }
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            if (ferror(stdin)) {
                return -1;
            }
            return 1;
        }
    }

    if (ferror(stdin)) {
        return -1;
    }

    *length = used;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[DATE_BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[DATE_BUFFER_SIZE];
    size_t length = 0U;
    int status;

    status = read_date(input, sizeof input, &length);
    if (status < 0) {
        fputs("Failed to read the date.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status > 0 ||
        convert_date(input, length, output, sizeof output) != 0) {
        fputs("Invalid date format.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs(output, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}