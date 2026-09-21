#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || a > UINT64_MAX - b) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int multiply_u64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || (a != 0 && b > UINT64_MAX / a)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int triangular_u64(uint64_t n, uint64_t *result)
{
    uint64_t a = n;
    uint64_t b;

    if (result == NULL || !add_u64(n, UINT64_C(1), &b)) {
        return 0;
    }

    if ((a & UINT64_C(1)) == 0) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    return multiply_u64(a, b, result);
}

static int sum_squares_u64(uint64_t n, uint64_t *result)
{
    uint64_t a = n;
    uint64_t b;
    uint64_t c;

    if (result == NULL ||
        !add_u64(n, UINT64_C(1), &b) ||
        !add_u64(n, n, &c) ||
        !add_u64(c, UINT64_C(1), &c)) {
        return 0;
    }

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

    if (!multiply_u64(a, b, &a)) {
        return 0;
    }

    return multiply_u64(a, c, result);
}

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t side;
    uint64_t other;
    uint64_t triangular;
    uint64_t squares;
    uint64_t product;
    uint64_t adjustment;

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

    if (!triangular_u64(side, &triangular) ||
        !sum_squares_u64(side, &squares) ||
        squares < triangular ||
        !multiply_u64(other, triangular, &product)) {
        return 0;
    }

    adjustment = squares - triangular;

    if (product < adjustment) {
        return 0;
    }

    *result = product - adjustment;
    return 1;
}

static int parse_dimensions(const char *line, uint64_t *width, uint64_t *height)
{
    const char *cursor;
    char *end;
    uintmax_t first;
    uintmax_t second;

    if (line == NULL || width == NULL || height == NULL) {
        return 0;
    }

    cursor = line;
    errno = 0;
    first = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || first > UINT64_MAX) {
        return 0;
    }

    cursor = end;
    errno = 0;
    second = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || second > UINT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *width = (uint64_t)first;
    *height = (uint64_t)second;
    return 1;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity || new_capacity <= length + 1) {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *line;
    uint64_t width;
    uint64_t height;
    uint64_t result;

    line = read_line(stdin);
    if (line == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!parse_dimensions(line, &width, &height)) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

    if (!count_squares(width, height, &result)) {
        fputs("Invalid dimensions or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}