#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
    uintmax_t n;
    uintmax_t a;
    uintmax_t b;

    if (count == NULL || length > UINTMAX_MAX) {
        return -1;
    }

    n = (uintmax_t)length;

    if (n == UINTMAX_MAX) {
        return -1;
    }

    a = n;
    b = n + UINTMAX_C(1);

    if ((a & UINTMAX_C(1)) == 0U) {
        a /= UINTMAX_C(2);
    } else {
        b /= UINTMAX_C(2);
    }

    if (a != 0U && b > UINTMAX_MAX / a) {
        return -1;
    }

    *count = a * b;
    return 0;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data;
    size_t capacity = 128U;
    size_t used = 0U;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0U;

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                free(data);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used == capacity - 1U) {
            char *resized;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(data);
                return -1;
            }

            new_capacity = capacity * 2U;
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

    data[used] = '\0';
    *buffer = data;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    uintmax_t count = 0U;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &input, &length) != 0) {
        goto cleanup;
    }

    if (count_nonempty_substrings(length, &count) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}