#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define INPUT_CAPACITY 4096U

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

static int read_line(char *buffer, size_t capacity, size_t *length)
{
    size_t used = 0U;
    int ch;

    if (buffer == NULL || length == NULL || capacity == 0U) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (used + 1U >= capacity) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            return -1;
        }

        buffer[used++] = (char)ch;
    }

    if (ferror(stdin)) {
        return -1;
    }

    buffer[used] = '\0';
    *length = used;
    return 0;
}

int main(void)
{
    char input[INPUT_CAPACITY];
    size_t length;
    uintmax_t count;

    if (read_line(input, sizeof input, &length) != 0) {
        return 1;
    }

    if (count_nonempty_substrings(length, &count) != 0) {
        return 1;
    }

    if (printf("%" PRIuMAX "\n", count) < 0) {
        return 1;
    }

    return 0;
}