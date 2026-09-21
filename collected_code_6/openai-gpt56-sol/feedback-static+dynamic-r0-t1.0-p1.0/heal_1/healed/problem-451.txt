#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int remove_whitespace(char *string, size_t *length)
{
    size_t read_index;
    size_t write_index = 0;

    if (string == NULL || length == NULL) {
        return -1;
    }

    for (read_index = 0; read_index < *length; ++read_index) {
        unsigned char c = (unsigned char)string[read_index];

        if (c != ' ' && c != '\t' && c != '\n' &&
            c != '\r' && c != '\f' && c != '\v') {
            string[write_index++] = string[read_index];
        }
    }

    string[write_index] = '\0';
    *length = write_index;
    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t input_length;
    size_t length;
    int result = EXIT_FAILURE;

    input_length = getline(&line, &capacity, stdin);
    if (input_length < 0) {
        result = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(line);
        return result;
    }

    length = (size_t)input_length;

    if (remove_whitespace(line, &length) == 0 &&
        fwrite(line, 1, length, stdout) == length &&
        fputc('\n', stdout) != EOF) {
        result = EXIT_SUCCESS;
    }

    free(line);
    return result;
}