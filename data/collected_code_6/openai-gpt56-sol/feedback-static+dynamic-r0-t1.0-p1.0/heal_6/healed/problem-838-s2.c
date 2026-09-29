#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_LENGTH ((size_t)100000)

static int minimum_swaps(const char *first, const char *second,
                         size_t length, size_t *result)
{
    size_t zero_one = 0;
    size_t one_zero = 0;

    if (first == NULL || second == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if ((first[i] != '0' && first[i] != '1') ||
            (second[i] != '0' && second[i] != '1')) {
            return 0;
        }

        if (first[i] == '0' && second[i] == '1') {
            ++zero_one;
        } else if (first[i] == '1' && second[i] == '0') {
            ++one_zero;
        }
    }

    if ((zero_one & 1U) != (one_zero & 1U)) {
        return 0;
    }

    *result = zero_one / 2U + one_zero / 2U;

    if ((zero_one & 1U) != 0U) {
        *result += 2U;
    }

    return 1;
}

static int is_space_char(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int discard_line(FILE *stream)
{
    int ch;

    if (stream == NULL) {
        return 0;
    }

    while ((ch = fgetc(stream)) != '\n' && ch != EOF) {
    }

    return ch != EOF;
}

static int read_binary_string(FILE *stream, char *buffer,
                              size_t capacity, size_t *length)
{
    size_t used = 0;
    int ch;

    if (stream == NULL || buffer == NULL || length == NULL ||
        capacity < 2U || capacity > MAX_LENGTH + 1U) {
        return 0;
    }

    buffer[0] = '\0';
    *length = 0;

    do {
        ch = fgetc(stream);
        if (ch == EOF) {
            return 0;
        }
    } while (is_space_char(ch));

    while (ch != EOF && !is_space_char(ch)) {
        if (ch != '0' && ch != '1') {
            discard_line(stream);
            return 0;
        }

        if (used >= capacity - 1U) {
            discard_line(stream);
            return 0;
        }

        buffer[used++] = (char)ch;
        ch = fgetc(stream);
    }

    if (ferror(stream)) {
        return 0;
    }

    buffer[used] = '\0';
    *length = used;
    return used != 0U;
}

int main(void)
{
    const size_t capacity = MAX_LENGTH + 1U;
    char *first = NULL;
    char *second = NULL;
    size_t first_length = 0;
    size_t second_length = 0;
    size_t swaps = 0;
    int status = EXIT_SUCCESS;

    first = malloc(capacity);
    second = malloc(capacity);

    if (first == NULL || second == NULL) {
        fputs("Memory allocation failed\n", stderr);
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (!read_binary_string(stdin, first, capacity, &first_length) ||
        !read_binary_string(stdin, second, capacity, &second_length)) {
        fputs("Invalid input\n", stderr);
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (first_length != second_length ||
        !minimum_swaps(first, second, first_length, &swaps)) {
        puts("-1");
    } else {
        printf("%zu\n", swaps);
    }

cleanup:
    free(second);
    free(first);
    return status;
}