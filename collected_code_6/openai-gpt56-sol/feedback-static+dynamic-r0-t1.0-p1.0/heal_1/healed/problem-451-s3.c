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
    size_t length;
    ssize_t result;

    result = getline(&line, &capacity, stdin);
    if (result < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    length = (size_t)result;

    if (remove_whitespace(line, &length) != 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (fwrite(line, 1, length, stdout) != length) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}