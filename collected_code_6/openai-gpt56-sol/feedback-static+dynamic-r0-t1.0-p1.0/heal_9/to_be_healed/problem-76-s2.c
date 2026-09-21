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
    } else if (c % UINT64_C(3) == 0) {
        c /= UINT64_C(3);
    } else {
        return 0;
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

static int is_space_char(unsigned char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\n' || ch == '\v' || ch == '\f';
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

    while (is_space_char((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        return 0;
    }

    errno = 0;
    first = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || first > UINT64_MAX) {
        return 0;
    }

    cursor = end;

    if (!is_space_char((unsigned char)*cursor)) {
        return 0;
    }

    while (is_space_char((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        return 0;
    }

    errno = 0;
    second = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || second > UINT64_MAX) {
        return 0;
    }

    while (is_space_char((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *width = (uint64_t)first;
    *height = (uint64_t)second;
    return 1;
}

static int discard_line(FILE *stream)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char discard[256];

    for (;;) {
        if (fgets(discard, sizeof discard, stream) == NULL) {
            return feof(stream) && !ferror(stream);
        }

        for (size_t i = 0; discard[i] != '\0'; ++i) {
            if (discard[i] == '\n') {
                return 1;
            }
        }
    }
}

static int read_line(FILE *stream, char **line)
{
    enum { MAX_LINE_LENGTH = 4096 };
    char *buffer;
    size_t length;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc((size_t)MAX_LINE_LENGTH + 1);
    if (buffer == NULL) {
        return 0;
    }

    if (fgets(buffer, MAX_LINE_LENGTH + 1, stream) == NULL) {
        free(buffer);
        return 0;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (!feof(stream)) {
        int discarded = discard_line(stream);
        free(buffer);
        /* Possible weaknesses found:
         *  Same value in both branches of ternary operator. [duplicateValueTernary]
         */
        return discarded ? 0 : 0;
    }

    if (ferror(stream)) {
        free(buffer);
        return 0;
    }

    *line = buffer;
    return 1;
}

int main(void)
{
    char *line = NULL;
    uint64_t width;
    uint64_t height;
    uint64_t result;

    if (!read_line(stdin, &line)) {
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