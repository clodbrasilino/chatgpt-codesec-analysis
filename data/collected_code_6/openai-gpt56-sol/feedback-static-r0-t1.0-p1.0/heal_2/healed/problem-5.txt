#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_tilings(size_t n, uint64_t *result)
{
    uint64_t previous = 1;
    uint64_t current = 3;

    if (result == NULL) {
        return -1;
    }

    if ((n & 1U) != 0U) {
        *result = 0;
        return 0;
    }

    if (n == 0U) {
        *result = previous;
        return 0;
    }

    for (size_t width = 4U; width <= n; width += 2U) {
        uint64_t next;

        if (current > UINT64_MAX / UINT64_C(4)) {
            return -1;
        }

        if (previous > UINT64_C(4) * current) {
            return -1;
        }

        next = UINT64_C(4) * current - previous;
        previous = current;
        current = next;

        if (width > SIZE_MAX - 2U) {
            break;
        }
    }

    *result = current;
    return 0;
}

static int read_line(char **line, size_t *length)
{
    char *buffer;
    size_t capacity = 64U;
    size_t used = 0U;

    if (line == NULL || length == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || used == 0U) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (used == capacity - 1U) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return -1;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    size_t length = 0U;
    uintmax_t parsed;
    uint64_t result;

    if (read_line(&input, &length) != 0) {
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > SIZE_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (count_tilings((size_t)parsed, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}