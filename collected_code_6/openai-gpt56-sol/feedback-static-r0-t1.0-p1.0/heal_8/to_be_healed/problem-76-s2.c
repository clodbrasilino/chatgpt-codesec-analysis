#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 4096U

static int checked_add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || a > UINT64_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int checked_mul_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || (a != 0 && b > UINT64_MAX / a)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int triangular_u64(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    return checked_mul_u64(a, b, result);
}

static int sum_squares_u64(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t product;

    if (result == NULL ||
        n > (UINT64_MAX - UINT64_C(1)) / UINT64_C(2)) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);
    c = UINT64_C(2) * n + UINT64_C(1);

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    if (a % UINT64_C(3) == 0) {
        a /= UINT64_C(3);
    } else if (b % UINT64_C(3) == 0) {
        b /= UINT64_C(3);
    } else {
        c /= UINT64_C(3);
    }

    if (!checked_mul_u64(a, b, &product)) {
        return 0;
    }

    return checked_mul_u64(product, c, result);
}

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t side;
    uint64_t other;
    uint64_t factor;
    uint64_t triangular;
    uint64_t square_sum;
    uint64_t product;

    if (result == NULL || width == 0 || height == 0) {
        return 0;
    }

    if (width < height) {
        side = width;
        other = height;
    } else {
        side = height;
        other = width;
    }

    if (!checked_add_u64(other, UINT64_C(1), &factor) ||
        !triangular_u64(side, &triangular) ||
        !sum_squares_u64(side, &square_sum) ||
        !checked_mul_u64(factor, triangular, &product) ||
        square_sum > product) {
        return 0;
    }

    *result = product - square_sum;
    return 1;
}

static int parse_u64(const char **cursor, uint64_t *value)
{
    const char *p;
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    p = *cursor;

    while (isspace((unsigned char)*p)) {
        ++p;
    }

    if (*p == '\0' || *p == '-' || *p == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(p, &end, 10);

    if (end == p || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *cursor = end;
    return 1;
}

static int read_line(char **line, size_t *length)
{
    char *buffer;
    size_t capacity;
    size_t used;
    int ch;

    if (line == NULL || length == NULL) {
        return -1;
    }

    capacity = 128U;
    used = 0U;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *expanded;
        /* Possible weaknesses found:
         *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
         */
        size_t new_capacity;

        if (used >= MAX_INPUT_LENGTH) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            free(buffer);

            if (ch == EOF && ferror(stdin)) {
                return -1;
            }

            return -2;
        }

        if (used + 1U >= capacity) {
            if (capacity > (size_t)MAX_INPUT_LENGTH / 2U) {
                new_capacity = (size_t)MAX_INPUT_LENGTH + 1U;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return -1;
            }

            expanded = realloc(buffer, new_capacity);
            if (expanded == NULL) {
                free(buffer);
                return -1;
            }

            buffer = expanded;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin)) {
            free(buffer);
            return -1;
        }

        if (used == 0U) {
            free(buffer);
            return 0;
        }
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input;
    const char *cursor;
    size_t input_length;
    uint64_t width;
    uint64_t height;
    uint64_t result;
    int read_status;

    input = NULL;
    input_length = 0U;
    read_status = read_line(&input, &input_length);

    if (read_status < 0) {
        if (read_status == -2) {
            fputs("Invalid input\n", stderr);
        } else {
            fputs("Input failure\n", stderr);
        }

        return EXIT_FAILURE;
    }

    if (read_status == 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_u64(&cursor, &width) ||
        !parse_u64(&cursor, &height)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!count_squares(width, height, &result)) {
        fputs("Invalid dimensions or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        fputs("Output failure\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}