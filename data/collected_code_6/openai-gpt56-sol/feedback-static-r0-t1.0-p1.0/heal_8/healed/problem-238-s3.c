#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>

#define INPUT_CAPACITY 4096U

static int count_non_empty_substrings(size_t length, uint64_t *count)
{
    uint64_t len;
    uint64_t first;
    uint64_t second;

    if (count == NULL) {
        return -1;
    }

#if SIZE_MAX > UINT64_MAX
    if (length > UINT64_MAX) {
        return -1;
    }
#endif

    len = (uint64_t)length;

    if ((len & UINT64_C(1)) == 0U) {
        first = len / UINT64_C(2);
        second = len + UINT64_C(1);
    } else {
        first = len;
        second = (len / UINT64_C(2)) + UINT64_C(1);
    }

    if (first != UINT64_C(0) && second > UINT64_MAX / first) {
        return -1;
    }

    *count = first * second;
    return 0;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data;
    size_t capacity = INPUT_CAPACITY;
    size_t used = 0U;
    int ch;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
        if (used == capacity - 1U) {
            char *expanded;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(data);
                return -1;
            }

            new_capacity = capacity * 2U;
            expanded = realloc(data, new_capacity);
            if (expanded == NULL) {
                free(data);
                return -1;
            }

            data = expanded;
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
    size_t length;
    uint64_t count;

    if (read_line(stdin, &input, &length) != 0) {
        return EXIT_FAILURE;
    }

    if (count_non_empty_substrings(length, &count) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu64 "\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}