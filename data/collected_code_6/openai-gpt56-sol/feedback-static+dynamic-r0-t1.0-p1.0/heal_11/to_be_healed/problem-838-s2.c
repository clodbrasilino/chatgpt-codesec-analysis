#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_LENGTH ((size_t)100000)

static int is_space_char(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int discard_token(FILE *stream, int ch)
{
    while (ch != EOF && !is_space_char(ch)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    }

    return ch != EOF || !ferror(stream);
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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
        if (ch == EOF) {
            return 0;
        }
    } while (is_space_char(ch));

    while (ch != EOF && !is_space_char(ch)) {
        if (ch != '0' && ch != '1') {
            if (!discard_token(stream, ch) && ferror(stream)) {
                clearerr(stream);
            }
            buffer[0] = '\0';
            return 0;
        }

        if (used + 1U >= capacity) {
            if (!discard_token(stream, ch) && ferror(stream)) {
                clearerr(stream);
            }
            buffer[0] = '\0';
            return 0;
        }

        buffer[used++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    }

    if (ch == EOF && ferror(stream)) {
        buffer[0] = '\0';
        return 0;
    }

    buffer[used] = '\0';
    *length = used;
    return 1;
}

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

int main(void)
{
    const size_t capacity = MAX_LENGTH + 1U;
    char *first = malloc(capacity);
    char *second = malloc(capacity);
    size_t first_length = 0;
    size_t second_length = 0;
    size_t swaps = 0;
    int status = EXIT_SUCCESS;

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