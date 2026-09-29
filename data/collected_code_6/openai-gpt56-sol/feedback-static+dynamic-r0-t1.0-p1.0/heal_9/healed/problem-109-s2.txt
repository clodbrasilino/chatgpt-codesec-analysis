#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum { MAX_INPUT_LENGTH = 1024 * 1024 };

static int read_binary_input(char *binary, size_t capacity, size_t *length)
{
    size_t used = 0;
    int ch = EOF;

    if (binary == NULL || length == NULL || capacity == 0) {
        return 0;
    }

    while (used < capacity && (ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stdin);
            if (next != '\n') {
                return 0;
            }
            ch = '\n';
            break;
        }

        if (ch != '0' && ch != '1') {
            return 0;
        }

        binary[used++] = (char)ch;
    }

    if (ferror(stdin) || used == 0) {
        return 0;
    }

    if (used == capacity && ch != '\n' && ch != EOF) {
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            return 0;
        }
    }

    if (ch == '\n') {
        ch = fgetc(stdin);
        if (ch != EOF || ferror(stdin)) {
            return 0;
        }
    }

    binary[used] = '\0';
    *length = used;
    return 1;
}

static int count_odd_rotations(const char *binary, size_t length,
                               size_t *count)
{
    size_t odd_count = 0;

    if (binary == NULL || count == NULL || length == 0) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (binary[i] == '1') {
            ++odd_count;
        } else if (binary[i] != '0') {
            return 0;
        }
    }

    *count = odd_count;
    return 1;
}

int main(void)
{
    char *binary = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    size_t length;
    size_t odd_rotations;
    int status = EXIT_FAILURE;

    if (binary == NULL) {
        return EXIT_FAILURE;
    }

    if (!read_binary_input(binary, (size_t)MAX_INPUT_LENGTH, &length)) {
        goto cleanup;
    }

    if (!count_odd_rotations(binary, length, &odd_rotations)) {
        goto cleanup;
    }

    if (printf("%zu\n", odd_rotations) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(binary);
    return status;
}