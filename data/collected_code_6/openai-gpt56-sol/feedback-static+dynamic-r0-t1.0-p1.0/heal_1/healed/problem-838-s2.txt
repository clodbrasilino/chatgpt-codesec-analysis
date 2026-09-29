#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_LENGTH 100000U

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

    if (zero_one / 2U > SIZE_MAX - one_zero / 2U) {
        return 0;
    }

    *result = zero_one / 2U + one_zero / 2U;

    if ((zero_one & 1U) != 0U) {
        if (*result > SIZE_MAX - 2U) {
            return 0;
        }
        *result += 2U;
    }

    return 1;
}

static int read_binary_string(char *buffer, size_t capacity, size_t *length)
{
    int ch;
    size_t used = 0;

    if (buffer == NULL || length == NULL || capacity == 0U) {
        return 0;
    }

    do {
        ch = getchar();
    } while (ch != EOF && (ch == ' ' || ch == '\t' ||
                            ch == '\n' || ch == '\r' ||
                            ch == '\f' || ch == '\v'));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && ch != ' ' && ch != '\t' &&
           ch != '\n' && ch != '\r' && ch != '\f' && ch != '\v') {
        if (ch != '0' && ch != '1') {
            do {
                ch = getchar();
            } while (ch != EOF && ch != ' ' && ch != '\t' &&
                     ch != '\n' && ch != '\r' && ch != '\f' && ch != '\v');
            return 0;
        }

        if (used + 1U >= capacity) {
            do {
                ch = getchar();
            } while (ch != EOF && ch != ' ' && ch != '\t' &&
                     ch != '\n' && ch != '\r' && ch != '\f' && ch != '\v');
            return 0;
        }

        buffer[used++] = (char)ch;
        ch = getchar();
    }

    if (used == 0U) {
        return 0;
    }

    buffer[used] = '\0';
    *length = used;
    return 1;
}

int main(void)
{
    char *first = malloc(MAX_LENGTH + 1U);
    char *second = malloc(MAX_LENGTH + 1U);
    size_t first_length;
    size_t second_length;
    size_t swaps;

    if (first == NULL || second == NULL) {
        free(first);
        free(second);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (!read_binary_string(first, MAX_LENGTH + 1U, &first_length) ||
        !read_binary_string(second, MAX_LENGTH + 1U, &second_length)) {
        free(first);
        free(second);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (first_length != second_length ||
        !minimum_swaps(first, second, first_length, &swaps)) {
        printf("-1\n");
    } else {
        printf("%zu\n", swaps);
    }

    free(first);
    free(second);
    return EXIT_SUCCESS;
}