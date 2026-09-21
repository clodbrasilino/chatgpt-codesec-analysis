#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int remove_whitespace(char *string, size_t *length)
{
    size_t read_pos;
    size_t write_pos = 0;

    if (string == NULL || length == NULL) {
        return -1;
    }

    for (read_pos = 0; read_pos < *length; ++read_pos) {
        unsigned char c = (unsigned char)string[read_pos];

        if (c != ' ' && c != '\t' && c != '\n' &&
            c != '\r' && c != '\f' && c != '\v') {
            string[write_pos++] = string[read_pos];
        }
    }

    string[write_pos] = '\0';
    *length = write_pos;
    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length;
    ssize_t result;
    int exit_status = EXIT_FAILURE;

    result = getline(&line, &capacity, stdin);
    if (result < 0) {
        goto cleanup;
    }

    length = (size_t)result;

    if (remove_whitespace(line, &length) != 0) {
        goto cleanup;
    }

    if (length > 0 && fwrite(line, 1, length, stdout) != length) {
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(line);
    return exit_status;
}