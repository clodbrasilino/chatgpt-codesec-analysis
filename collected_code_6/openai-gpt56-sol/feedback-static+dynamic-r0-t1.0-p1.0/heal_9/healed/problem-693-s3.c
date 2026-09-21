#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int append_byte(char **data, size_t *length, size_t *capacity,
                       unsigned char byte)
{
    char *resized;

    if (data == NULL || length == NULL || capacity == NULL ||
        *length > *capacity ||
        (*data == NULL && *capacity != 0) ||
        *length == SIZE_MAX) {
        return -1;
    }

    if (*length == *capacity) {
        size_t new_capacity;

        if (*capacity == 0) {
            new_capacity = 128;
        } else if (*capacity > SIZE_MAX / 2) {
            new_capacity = SIZE_MAX;
        } else {
            new_capacity = *capacity * 2;
        }

        if (new_capacity <= *length) {
            return -1;
        }

        resized = realloc(*data, new_capacity);
        if (resized == NULL) {
            return -1;
        }

        *data = resized;
        *capacity = new_capacity;
    }

    (*data)[*length] = (char)byte;
    ++*length;

    return 0;
}

static int remove_multiple_spaces(const char *input, size_t input_len,
                                  char **output, size_t *output_len)
{
    char *result;
    size_t read_pos;
    size_t write_pos = 0;
    int previous_space = 0;

    if (output == NULL || output_len == NULL ||
        (input == NULL && input_len != 0) ||
        input_len == SIZE_MAX) {
        return -1;
    }

    *output = NULL;
    *output_len = 0;

    result = malloc(input_len + 1);
    if (result == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < input_len; ++read_pos) {
        unsigned char current = (unsigned char)input[read_pos];

        if (current == (unsigned char)' ') {
            if (previous_space) {
                continue;
            }
            previous_space = 1;
        } else {
            previous_space = 0;
        }

        result[write_pos++] = (char)current;
    }

    result[write_pos] = '\0';
    *output = result;
    *output_len = write_pos;

    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t input_len = 0;
    size_t input_capacity = 0;
    size_t output_len = 0;
    int status = EXIT_FAILURE;
    unsigned char buffer[4096];

    for (;;) {
        size_t count = fread(buffer, 1, sizeof buffer, stdin);
        size_t i;

        for (i = 0; i < count; ++i) {
            if (buffer[i] == (unsigned char)'\n') {
                goto input_complete;
            }

            if (append_byte(&input, &input_len, &input_capacity,
                            buffer[i]) != 0) {
                goto cleanup;
            }
        }

        if (count < sizeof buffer) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }
    }

input_complete:
    if (remove_multiple_spaces(input, input_len, &output, &output_len) != 0) {
        goto cleanup;
    }

    if (output_len != 0 &&
        fwrite(output, 1, output_len, stdout) != output_len) {
        goto cleanup;
    }

    if (fputc('\n', stdout) == EOF || fflush(stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}