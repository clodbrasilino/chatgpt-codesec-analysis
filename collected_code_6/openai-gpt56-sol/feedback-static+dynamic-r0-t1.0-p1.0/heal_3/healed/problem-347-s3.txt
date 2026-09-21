#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

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

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t minimum;
    uint64_t maximum;
    uint64_t n_plus_one;
    uint64_t two_n_plus_one;
    uint64_t triangular;
    uint64_t square_sum;
    uint64_t total;
    uint64_t x;
    uint64_t y;

    if (result == NULL || width == 0 || height == 0) {
        return 0;
    }

    minimum = width < height ? width : height;
    maximum = width < height ? height : width;

    if (!add_u64(minimum, UINT64_C(1), &n_plus_one)) {
        return 0;
    }

    x = minimum;
    y = n_plus_one;

    if ((x & UINT64_C(1)) == 0) {
        x /= UINT64_C(2);
    } else {
        y /= UINT64_C(2);
    }

    if (!multiply_u64(x, y, &triangular)) {
        return 0;
    }

    if (minimum > (UINT64_MAX - UINT64_C(1)) / UINT64_C(2)) {
        return 0;
    }

    two_n_plus_one = minimum * UINT64_C(2) + UINT64_C(1);
    x = triangular;
    y = two_n_plus_one;

    if (x % UINT64_C(3) == 0) {
        x /= UINT64_C(3);
    } else if (y % UINT64_C(3) == 0) {
        y /= UINT64_C(3);
    } else {
        return 0;
    }

    if (!multiply_u64(x, y, &square_sum)) {
        return 0;
    }

    if (!add_u64(maximum, UINT64_C(1), &x)) {
        return 0;
    }

    if (!multiply_u64(triangular, x, &total) || total < square_sum) {
        return 0;
    }

    *result = total - square_sum;
    return 1;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    int ch;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int parse_u64(char **cursor, uint64_t *value)
{
    char *start;
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    start = *cursor;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '+' || *start == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *cursor = end;
    return 1;
}

static int read_dimensions(uint64_t *width, uint64_t *height)
{
    char *line;
    char *cursor;
    int valid;

    if (width == NULL || height == NULL) {
        return 0;
    }

    if (!read_line(&line)) {
        return 0;
    }

    cursor = line;
    valid = parse_u64(&cursor, width) && parse_u64(&cursor, height);

    if (valid) {
        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }
        valid = *cursor == '\0';
    }

    free(line);
    return valid;
}

int main(void)
{
    uint64_t width;
    uint64_t height;
    uint64_t result;

    if (!read_dimensions(&width, &height)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_squares(width, height, &result)) {
        fputs("Invalid dimensions or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}