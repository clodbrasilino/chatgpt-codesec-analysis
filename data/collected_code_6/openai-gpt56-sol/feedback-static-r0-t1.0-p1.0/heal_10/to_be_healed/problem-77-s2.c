#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int digit_sum_difference(const char *begin, const char *end, int *result)
{
    int even_sum = 0;
    int odd_sum = 0;

    if (begin == NULL || end == NULL || result == NULL || begin > end) {
        return 0;
    }

    if (begin < end && (*begin == '+' || *begin == '-')) {
        ++begin;
    }

    if (begin == end) {
        return 0;
    }

    while (begin < end) {
        unsigned char ch = (unsigned char)*begin;
        int digit;

        if (!isdigit(ch)) {
            return 0;
        }

        digit = (int)(ch - (unsigned char)'0');

        if ((digit & 1) == 0) {
            if (even_sum > INT_MAX - digit) {
                return 0;
            }
            even_sum += digit;
        } else {
            if (odd_sum > INT_MAX - digit) {
                return 0;
            }
            odd_sum += digit;
        }

        ++begin;
    }

    *result = even_sum - odd_sum;
    return 1;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data;
    size_t used = 0;
    size_t capacity = 128;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0;

    data = malloc(capacity);
    if (data == NULL) {
        return 0;
    }

    for (;;) {
        int ch;

        if (used == capacity - 1) {
            size_t new_capacity;
            char *new_data;

            if (capacity > SIZE_MAX / 2) {
                free(data);
                return 0;
            }

            new_capacity = capacity * 2;
            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return 0;
            }

            data = new_data;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || used == 0) {
                free(data);
                return 0;
            }
            break;
        }

        data[used++] = (char)(unsigned char)ch;
    }

    if (used > 0 && data[used - 1] == '\r') {
        --used;
    }

    data[used] = '\0';
    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    const char *begin;
    const char *end;
    const char *number_end;
    int result;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &input, &length)) {
        return EXIT_FAILURE;
    }

    begin = input;

    while (*begin != '\0' && isspace((unsigned char)*begin)) {
        ++begin;
    }

    end = begin;

    if (*end == '+' || *end == '-') {
        ++end;
    }

    {
        const char *digits = end;

        while (*end != '\0' && isdigit((unsigned char)*end)) {
            ++end;
        }

        if (end == digits) {
            goto cleanup;
        }
    }

    number_end = end;

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    if (!digit_sum_difference(begin, number_end, &result)) {
        goto cleanup;
    }

    if (printf("%d\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}