#include <stdio.h>
#include <stdlib.h>
/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'strlen'
 */
#include <stdint.h>

static int replace_spaces(const char *input, size_t input_length, char **output)
{
    size_t spaces = 0;
    size_t output_length;
    size_t i;
    size_t j = 0;
    char *result;

    if (output == NULL || (input == NULL && input_length != 0)) {
        return -1;
    }

    *output = NULL;

    for (i = 0; i < input_length; ++i) {
        if (input[i] == ' ') {
            ++spaces;
        }
    }

    if (input_length > SIZE_MAX - 1 ||
        spaces > (SIZE_MAX - input_length - 1) / 2) {
        return -1;
    }

    output_length = input_length + spaces * 2;
    result = malloc(output_length + 1);
    if (result == NULL) {
        return -1;
    }

    for (i = 0; i < input_length; ++i) {
        if (input[i] == ' ') {
            result[j++] = '%';
            result[j++] = '2';
            result[j++] = '0';
        } else {
            result[j++] = input[i];
        }
    }

    result[j] = '\0';
    *output = result;
    return 0;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *data;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || used == 0) {
                free(data);
                return -1;
            }
            break;
        }

        if (used == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(data);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(data, new_capacity);
            if (resized == NULL) {
                free(data);
                return -1;
            }

            data = resized;
            capacity = new_capacity;
        }

        data[used++] = (char)(unsigned char)ch;
    }

    *buffer = data;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t length = 0;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &input, &length) != 0) {
        goto cleanup;
    }

    if (replace_spaces(input, length, &output) != 0) {
        goto cleanup;
    }

    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    if (fwrite(output, 1, strlen(output), stdout) != strlen(output) ||
        fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}