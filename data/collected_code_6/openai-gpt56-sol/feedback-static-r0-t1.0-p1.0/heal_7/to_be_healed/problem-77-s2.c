#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int digit_sum_difference(const char *begin, const char *end, int *result)
{
    int even_sum = 0;
    int odd_sum = 0;

    if (begin < end && (*begin == '+' || *begin == '-')) {
        ++begin;
    }

    while (begin < end) {
        int digit = (int)((unsigned char)*begin - (unsigned char)'0');

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
    char *data = NULL;
    size_t used = 0;
    size_t capacity = 0;
    int ch = EOF;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (used == SIZE_MAX - 1) {
            free(data);
            return 0;
        }

        if (used + 1 >= capacity) {
            size_t new_capacity;
            char *new_data;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(data);
                    return 0;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= used + 1) {
                free(data);
                return 0;
            }

            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return 0;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[used++] = (char)ch;
    }

    if (ferror(stream) || (used == 0 && ch == EOF)) {
        free(data);
        return 0;
    }

    if (data == NULL) {
        data = malloc(1);
        if (data == NULL) {
            return 0;
        }
    }

    data[used] = '\0';
    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input;
    size_t length;
    const char *begin;
    const char *end;
    const char *number_end;
    int result;

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
            free(input);
            return EXIT_FAILURE;
        }
    }

    number_end = end;

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    if (!digit_sum_difference(begin, number_end, &result)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}