#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum { MAX_INPUT_LENGTH = 1024 * 1024 };

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
    size_t length = 0;
    size_t odd_rotations = 0;
    int status = EXIT_FAILURE;
    int ch;

    if (binary == NULL) {
        return EXIT_FAILURE;
    }

    while (length < (size_t)MAX_INPUT_LENGTH) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        if (ch == '\n') {
            ch = fgetc(stdin);
            if (ch != EOF || ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        if (ch == '\r') {
            ch = fgetc(stdin);
            if (ch != '\n') {
                goto cleanup;
            }

            ch = fgetc(stdin);
            if (ch != EOF || ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        if (ch != '0' && ch != '1') {
            goto cleanup;
        }

        binary[length++] = (char)ch;
    }

    if (length == (size_t)MAX_INPUT_LENGTH) {
        ch = fgetc(stdin);

        if (ch == '\r') {
            ch = fgetc(stdin);
            if (ch != '\n') {
                goto cleanup;
            }
            ch = fgetc(stdin);
        } else if (ch == '\n') {
            ch = fgetc(stdin);
        }

        if (ch != EOF || ferror(stdin)) {
            goto cleanup;
        }
    }

    if (length == 0) {
        goto cleanup;
    }

    binary[length] = '\0';

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