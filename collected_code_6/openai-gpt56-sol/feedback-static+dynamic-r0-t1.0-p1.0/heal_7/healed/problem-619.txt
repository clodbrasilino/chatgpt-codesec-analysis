#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int move_numbers_to_end(char *str, size_t capacity)
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

    memmove(str, result, position + 1);
    free(result);

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t bytes_read;
    int status = EXIT_FAILURE;

    bytes_read = getline(&input, &capacity, stdin);
    if (bytes_read < 0) {
        goto cleanup;
    }

    if (bytes_read > 0 && input[(size_t)bytes_read - 1] == '\n') {
        input[(size_t)bytes_read - 1] = '\0';
    }

    if (move_numbers_to_end(input, capacity) != 0) {
        goto cleanup;
    }

    if (puts(input) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}