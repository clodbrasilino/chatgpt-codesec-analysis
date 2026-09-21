#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_nonempty_substrings(size_t length, uintmax_t *count)
{
    uintmax_t n;

    if (count == NULL || length > UINTMAX_MAX) {
        return -1;
    }

    n = (uintmax_t)length;

    if (n != 0U && n + 1U > UINTMAX_MAX / n) {
        return -1;
    }

    *count = n * (n + 1U) / 2U;
    return 0;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data;
    size_t capacity = 128U;
    size_t used = 0U;
    int ch;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
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

    if (ferror(stream)) {
        free(data);
        return -1;
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
    int status = 1;

    if (read_line(stdin, &input, &length) != 0) {
        goto cleanup;
    }

    if (count_nonempty_substrings(length, &count) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        goto cleanup;
    }

    status = 0;

cleanup:
    free(input);
    return status;
}