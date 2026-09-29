#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_LENGTH 100000U

static int minimum_swaps(const char *first, const char *second,
                         size_t length, size_t *result)
{
    size_t zero_one = 0U;
    size_t one_zero = 0U;

    if (first == NULL || second == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0U; i < length; ++i) {
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

static int read_binary_string(char *buffer, size_t capacity, size_t *length)
{
    int ch;
    size_t used = 0U;
    int valid = 1;

    if (buffer == NULL || length == NULL || capacity < 2U) {
        return 0;
    }

    *length = 0U;
    buffer[0] = '\0';

    do {
        ch = getchar();
    } while (ch != EOF && is_space_char(ch));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && !is_space_char(ch)) {
        if (ch != '0' && ch != '1') {
            valid = 0;
        } else if (used < capacity - 1U) {
            buffer[used++] = (char)ch;
        } else {
            valid = 0;
        }

        ch = getchar();
    }

    if (!valid || used == 0U) {
        buffer[0] = '\0';
        return 0;
    }

    buffer[used] = '\0';
    *length = used;
    return 1;
}

int main(void)
{
    const size_t capacity = (size_t)MAX_LENGTH + 1U;
    char *first = malloc(capacity);
    char *second = malloc(capacity);
    size_t first_length = 0U;
    size_t second_length = 0U;
    size_t swaps = 0U;
    int status = EXIT_SUCCESS;

    if (first == NULL || second == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (!read_binary_string(first, capacity, &first_length) ||
        !read_binary_string(second, capacity, &second_length)) {
        fprintf(stderr, "Invalid input\n");
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